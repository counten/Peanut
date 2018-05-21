/*
* Author: micle 2018/3/13
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn
*/

#include "HttpReq.h"
#include "../Util/StrUtil.h"

/**
 * @Desc Set request method;
 * */
void HttpReq::setMethod(const char* start, size_t len)
{
	method_.assign(start, start + len);
}

/**
 * @Desc Judge dynamic request or static request;
 * if static request complete the path of file map to request;
 * */
void HttpReq::setPath(const char* uri)
{
	// If uri contains parameters;

	std::string url = uri;
	url = url.substr(0, url.find_first_of('?'));
	if (_controllerMap.size() > 0 && _controllerMap.count(url))
    {
        // Dynamic request;
        path_ += uri;
        static_ = false;
        return;
	}
	else
    { // Static request
        path_ += rootDir_;
        path_ += url;

        if (uri[strlen(uri) - 1] == '/')
        {
            path_ += homePage_;
        }
        // request is static;
        static_ = true;
        return;
	}
}


/**
 * @Desc Clear data;
 * */
void HttpReq::reset()
{
    state_ = Peanut::RequestParseState::ExpectReqLine;
    path_.clear();
    contentLen_ = 0;
}

/**
 * @Desc Get mime type
 * */
const char* HttpReq::getFileType()
{
    if (strstr(path_.c_str(), ".html") || strstr(path_.c_str(), ".htm"))
        fileType_ = "text/html";
    else if (strstr(path_.c_str(), ".gif"))
        fileType_ = "image/gif";
    else if (strstr(path_.c_str(), ".jpg") || strstr(path_.c_str(), ".jpeg"))
        fileType_ = "image/jpeg";
    else if (strstr(path_.c_str(), ".png"))
        fileType_ = "image/png";
    else if (strstr(path_.c_str(), ".ico"))
        fileType_ = "image/ico";
    else if (strstr(path_.c_str(), ".css"))
        fileType_ = "text/css";
    else if (strstr(path_.c_str(), ".js"))
        fileType_ = "text/javascript";
    else if (strstr(path_.c_str(), ".ttf") || strstr(path_.c_str(), ".otf"))
        fileType_ = "application/octet-stream";
    else if (strstr(path_.c_str(),"woff"))
        fileType_ = "application/woff;charset=UTF-8";
    else if (strstr(path_.c_str(),"wasm"))
        fileType_ = "application/wasm";
    else if (strstr(path_.c_str(),"eot"))
        fileType_ = "application/eot;charset=UTF-8";
    else
        fileType_ =  "text/plain";
    return fileType_.c_str();
}

/**
 * @Desc Parse first line of request;
 * */
bool HttpReq::parseRequestLine(Buffer &buf)
{
    char method[64], path[256], version[64];
    char *line = buf.getLine();
    sscanf(line, "%s %s %s", method, path, version);
//    std::cout <<"\n报文流动2 起始行: "<< method <<" "<<path<<" "<< version << "\n";
    setMethod(method, strlen(method));
    setPath(path);
    delete[] line;
    return true;
}

/**
 * @Desc Parse headers except first line of request;
 * */
bool HttpReq::parseHeaders(Buffer &buf) // Other head info
{
    bool con = true;
    while (con)
    {
        char *line = buf.getLine();
        if(line == nullptr || strlen(line) == 0)
        {
            con = false;
            continue;
        }
        if (strstr(line, "keep-alive"))
        {
            keepAlive_ = true;
        }
        else if (strstr(line, "Content-Length"))
        {
            std::string len = line;
            len = len.substr(len.find_first_of(":") + 1);
            contentLen_ = Peanut::S2i(len);
        }
        // If have content_ store content_;
        else if(strstr(line, "<end>"))
        {
//            std::cout <<"\n报文流动2: 头部"<< line<<"\n";
            content_ = line;
            content_ = content_.substr(0, content_.find("<end>"));
//            std::cout<<"\ncontent:0 "<<content_<<"\n";
        }
        delete[] line;
    }
    return true;
}

/**
 * @Desc Parse request;
 * */
Peanut::RequestParseState HttpReq::parseRequest(Buffer& buf)
{
    bool hasMore = true;
    while (hasMore)
    {
        switch (state_)
        {
            case Peanut::RequestParseState::ExpectReqLine :
            {
                if (buf.findCRLF())
                { // If find;
                    if (parseRequestLine(buf))
                    {
                        state_ = Peanut::RequestParseState::ExpectHeaders;
                    }
                    else
                    {
                        state_ = Peanut::RequestParseState::Error;
                        hasMore = false;
                    }
                }
                else
                {// Have'nt means client have'nt send finish, keep listen.
                    hasMore = false;
                }
            }
                break;
            case Peanut::RequestParseState::ExpectHeaders :
            {
                if (parseHeaders(buf))
                {
                    state_ = Peanut::RequestParseState::GotAll;
                    hasMore = false;
                }
                else
                {
                    hasMore = false;
                }
            }
                break;
            case Peanut::RequestParseState::ExpectBody:
            {
                // TODO deal withe receive part of request
            }
                break;
        }
    }
    return state_;
}