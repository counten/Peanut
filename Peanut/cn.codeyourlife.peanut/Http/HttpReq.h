/*
* Author: micle 2018/3/13
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn
*/

#ifndef _HTTP_REQUEST_H_
#define _HTTP_REQUEST_H_

#include <string>
#include "IO/Buffer.h"
#include "../Conf/Defination.h"
#include "../Conf/Conf.h"

class HttpReq
{

private:
    Peanut::RequestParseState state_;

    // Dir of Static file;
    std::string rootDir_;

    // Home page;
    std::string homePage_;


    /**
     * @Desc Set request method;
     * */
    void setMethod(const char *start, size_t len);


    void setPath(const char *start);

public:
    bool keepAlive_;

    bool sendFile_;

    int contentLen_;

    std::string content_;

    // If static file support only;
    bool static_;

    std::string method_;

    std::string path_;

    std::string fileType_;

    HttpReq()
    {
        state_ = Peanut::RequestParseState::ExpectReqLine;
        rootDir_ = Peanut::getValue(CFG_STATIC, CFG_STATIC_DIR);
        homePage_ = Peanut::getValue(CFG_STATIC, CFG_STATIC_HOME);
    }

    /**
     * @Desc Get mime type
     * */
    const char *getFileType();

    /**
     * @Desc Clear data;
     * */
    void reset();


    /**
     * @Desc Parse first line of request;
     * */
    bool parseRequestLine(Buffer &buf);


    /**
     * @Desc Parse headers except first line of request;
     * */
    bool parseHeaders(Buffer &buf);

    /**
    * @Desc Parse request;
    * */
    Peanut::RequestParseState parseRequest(Buffer &buf);

};

#endif
