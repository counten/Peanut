/*
* Author: micle 2018/3/13
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn
*/

#ifndef _HTTP_HANDLE_H_
#define _HTTP_HANDLE_H_


#include "HttpReq.h"
#include "IO/Cache.h"
#include "IO/ReqInfo.h"
#include "../Conf/Defination.h"

class HttpHandle
{

public:
    ReqInfo reqInfo;

    void init(int sockFd, std::string clientIp);

    void process();

    static void setEPollFd(int ePollFd)
    {
        ePollFd_ = ePollFd;
    }


private:
    Peanut::HttpHandleState state_;

    HttpReq request_;

    static int ePollFd_;

    /* 该HTTP连接的socket和对方的socket地址 */
    int sockFd_;

    std::string clientIP_;

    std::shared_ptr<FileInfo> fileInfo_;

    Buffer readBuffer_;

    // Keep connect or not;
    bool keepAlive_;

    // Send file or not;
    bool sendFile_;

    // Write buffer;
    Buffer writeBuffer_;

    /* 已经写了多少字节 */
    size_t fileWritten_; /* 文件写了多少字节 */

    bool read();

    void processRead();

    void processWrite();

    void reset();


    /**
     * @Desc Response Exception like 500 or 404;
     * */
    void responseResult(const char *, const char *, const char *, const char *);

    /**
     * @Desc Response static request;
     * */
    void responseResult(const char *, size_t);


    /**
     * @Desc Response dynamic request;
     * */
    void responseResult(std::string);

};

#endif
