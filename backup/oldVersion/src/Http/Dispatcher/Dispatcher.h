/*
* Author: micle 2017/12/12
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#ifndef MNSERVER_DISPATCHER_H
#define MNSERVER_DISPATCHER_H

#include <map>

// Inner Project
#include "../IO/HttpReq.h"
#include "../IO/HttpRes.h"
#include "../../Util/FileUtil.h"
#include "../../Conf/Conf.h"
#include "../../Log/Log.h"
#include "../../../Logic/RootersMap.h"
#include "MnRequest.h"

#define METHOD_GET "GET"
#define METHOD_PUT "PUT"
#define METHOD_POST "POST"
#define METHOD_DELETE "DELETE"
#define METHOD_HEAD "HEAD"
#define METHOD_TRACE "TRACE"
#define METHOD_OPTIONS "OPTIONS"

class Dispatcher
{
private:
    std::string URL;
    std::string method;
    std::string protocal;
    std::string request;
    std::string content;
public:

    std::string getMethod();

    void setMethod(std::string method);

    std::string getProtocal();

    void setProtocal(const std::string &protocal);

    const std::string getURL();

    void setURL(std::string URL);

    std::string getRequest();

    void setRequest(std::string request);

    std::string getContent();

    void setContent(const std::string content);

    Dispatcher(std::string Req);

    /**
     * @param url
     * Set content to HTTPResponse;
     * @return 0 ok, 1 error;
     * */
    int url2Controller(std::string url, HttpRes &httpRes);

    int url2Controller(std::string url, std::string content, HttpRes &httpRes);

    /**
     * @param url
     * Set file content to HTTPResponse, set 404 file if does not get map file;
     * */
    void url2File(std::string url, HttpRes &httpRes);

    /**
     * @param url
     * Set content type of HTTPResponse, don't set if does not get map type;
     * */
    void url2CType(std::string url, HttpRes &httpRes);

    /**
     * @return Standard Http Response String map to the request;
     * */
    int getRes(unsigned char *send_buf);
};


#endif //MNSERVER_DISPATCHER_H
