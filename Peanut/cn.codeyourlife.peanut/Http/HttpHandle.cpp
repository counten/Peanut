#include "HttpHandle.h"
#include <sys/stat.h>
#include <sys/epoll.h>
#include <asm/socket.h>
#include <unistd.h>

// Inner project
#include "../Bin/EPollUtil.h"
#include "../Http/Tcp.h"

using namespace Peanut;

void HttpHandle::init(int sockFd, std::string clientIp)
{
    sockFd_ = sockFd; /* Record socket */
    clientIP_ = clientIp;
    /* 如下两行是为了避免TIME_WAIT状态,仅仅用于调试,实际使用时应该去掉 */
    //	int reuse = 1;
    //	SetSockOpt(sockFd_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)); /* 设置端口重用? */
    reset();
}

void HttpHandle::process()
{
    /**
    * 在process之前,只有这么一些状态kExpectRead, kExpectWrite
    */
    switch (state_)
    {
        case ExpectRead:
        {
            processRead();
            break;
        }
        case ExpectWrite:
        {
            processWrite();
            break;
        }
        default: /* close connection whether success or not */
            removeFd(ePollFd_, sockFd_);
            break;
    }
    /*-
    * 程序执行完成后,有这么一些状态kExpectRead, ExpectWrite, Error, Success
    */
    switch (state_)
    {
        case ExpectRead:
        {
            modFd(ePollFd_, sockFd_, EPOLLIN, true);
            break;
        }
        case ExpectWrite:
        {
            modFd(ePollFd_, sockFd_, EPOLLOUT, true);
            break;
        }
        default:
        {
            removeFd(ePollFd_, sockFd_);
            break;
        }
    }
}

bool HttpHandle::read()
{ /* 由于ePoll设置成了是边缘触发,所以要一次性将数据全部读尽 */
    int byteRead = 0;
    while (true)
    {
        int savedErrNo;
        byteRead = readBuffer_.readFd(sockFd_, &savedErrNo);
        if (byteRead == -1)
        {
            if ((savedErrNo == EAGAIN) || (savedErrNo == EWOULDBLOCK))
            {
                break; /* Read finish! */
            }
            state_ = Error; /* Read error */
            return false;
        }
        else if (byteRead == 0)
        { /* Connection have bean closed */
            state_ = Closed;
            return false;
        }
    }
    return true;
}

void HttpHandle::processRead()
{
	struct stat sbuf;

	if (!read())
    { // Read error means connection closed;
		state_ = Closed;
		return;
	}

    // TODO deal with get part request;
	Peanut::RequestParseState state = request_.parseRequest(readBuffer_);
	if (state == RequestParseState::Error)
    {
		state_ = Error; /* Parse error */
		return;
	}
	else if (state != RequestParseState::GotAll)
    { // Client send part of request keep reading;
		return;
	}

	                                     
	if (request_.static_)
    { // static request;
		if (stat(request_.path_.c_str(), &sbuf) < 0)
		{
            // Can not find file
            responseResult(request_.path_.c_str(), "404", "Not found", "Peanut couldn't find this file");
			goto end;
		}

        // Do not have authorize;
		if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode))
        {
            responseResult(request_.path_.c_str(), "403", "Forbidden", "Peanut couldn't read the file");
			goto end;
		}
        responseResult(request_.path_.c_str(), sbuf.st_size);
		
	}
	else
    { // Serve dynamic request;

        std::string result;

        // TODO dynamic request
        if(!strcasecmp(request_.method_.c_str(), METHOD_GET))
        {
            reqInfo.package(this->clientIP_, request_.path_);
            // if contains parameter cut it;
            std::string url = request_.path_;
            url = url.substr(0, url.find_first_of('?'));
            result = (*_controllerMap[url])(reqInfo);
      }
        else if(!strcasecmp(request_.method_.c_str(), METHOD_POST))
        {
            reqInfo.package(this->clientIP_, request_.path_, request_.content_);
            // if contains parameter cut it;
            std::string url = request_.path_;
            url = url.substr(0, url.find_first_of('?'));
            result = (*_controllerMap[url])(reqInfo);
        }
        else
        {
            responseResult(request_.method_.c_str(), "501", "Method Not Implemented",
                           "Peanut does not implement this method");
            goto end;
        }

        responseResult(result);
		goto end;
	}

end:
	state_ = ExpectWrite;
	return processWrite();
}

void HttpHandle::reset()
{
	keepAlive_ = false;
	sendFile_ = false;
	fileWritten_ = 0;
	readBuffer_.retrieveAll();
	writeBuffer_.retrieveAll();
	request_.reset();
    reqInfo.reset();
	state_ = ExpectRead;
}

void HttpHandle::processWrite()
{
	ssize_t res;

    /** Send writeBuf_ first*/
	size_t nRemain = writeBuffer_.readAbleSize(); /* writeBuf_中还有多少字节要写 */
	if (nRemain > 0)
    {
		while (true)
        {
			size_t len = writeBuffer_.readAbleSize();
			res = write(sockFd_, writeBuffer_.readLoc(), len);
			if (res < 0)
            {
				if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
                { /* 资源暂时不可用 */
					return;
				}
				state_ = Error;
				return;
			}
			writeBuffer_.retrieve(res);
			if (writeBuffer_.readAbleSize() == 0)
            {
                break;
            }
		}
	}

    /** If need to send file*/
	if (sendFile_)
    {
		char *fileAdd = (char *)fileInfo_->add_;
		size_t fileSize = fileInfo_->size_;
		while (true)
        {
			res = write(sockFd_, fileAdd + fileWritten_, fileSize - fileWritten_);
			if (res < 0)
            {
				if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
                { /* 资源暂时不可用 */
					return;
				}
				state_ = Error; /* 出现了错误 */
				return;
			}
			fileWritten_ += res;
			if (fileWritten_ == fileInfo_->size_)
            {
                break;
            }
		}
		
	}

	// Data send finished;
    logSuccess("Send OK");
	reset();
	state_ = keepAlive_? ExpectRead : Success;
}

/**
 * Response deal function************************************************************
 * */
Cache _staticFileCache;

int HttpHandle::ePollFd_ = -1;


void HttpHandle::responseResult(const char *cause, const char *errNum, const char *shortMsg, const char *longMsg)
{
    char  body[1024];

    /* Build the HTTP response body */
    sprintf(body, "<html><title>Peanut Error</title>");
    sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
    sprintf(body, "%s%s: %s\r\n", body, errNum, shortMsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longMsg, cause);
    sprintf(body, "%s<hr><em><a href=\"http://codeyourlife.cn\">Peanut</a></em>\r\n", body);

    /* Print the HTTP response */
    writeBuffer_.appendStr("HTTP/1.0 %s %s\r\n", errNum, shortMsg);
    writeBuffer_.appendStr("Content-type: text/html\r\n");
    writeBuffer_.appendStr("Content-length: %d\r\n\r\n", (int)strlen(body));
    writeBuffer_.appendStr("%s", body);
}

void HttpHandle::responseResult(const char *fileName, size_t fileSize)
{
    writeBuffer_.appendStr("HTTP/1.0 200 OK\r\n");
    writeBuffer_.appendStr("Server: Peanut\r\n");
    writeBuffer_.appendStr("Content-length: %d\r\n", fileSize);
    writeBuffer_.appendStr("Content-type: %s\r\n\r\n", request_.getFileType());

    _staticFileCache.getFileAdd(fileName, fileSize, fileInfo_); // Get file Info from cache;
    sendFile_ = true;
}

void HttpHandle::responseResult(std::string content)
{
    writeBuffer_.appendStr("HTTP/1.0 200 OK\r\n");
    writeBuffer_.appendStr("Server: Peanut\r\n");
    writeBuffer_.appendStr("Content-length: %d\r\n", content.length());
    writeBuffer_.appendStr("Content-type: %s\r\n\r\n", "text/html;charset=UTF-8");
    writeBuffer_.append(content.c_str(), content.length());
//    std::cout <<"\n报文流动4 构造响应报文: \n";
    sendFile_ = false;
}
