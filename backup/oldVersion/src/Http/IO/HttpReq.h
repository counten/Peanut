/*
* Author: micle 2017/12/14
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#ifndef MNSERVER_HTTPREQ_H
#define MNSERVER_HTTPREQ_H


#include <iostream>
#include <vector>

// Inner Project
#include "../../Util/StrUtil.h"

class HttpReq
{
private:
    std::string method;
    std::string url;
    std::string protocal;
    std::string content;
    std::map<std::string, std::string> info;

public:
    std::string getMethod();

    void setMethod(std::string method);

    std::string getUrl();

    void setUrl(std::string url);

    std::string getProtocal();

    void setProtocal(std::string protocal);

    std::map<std::string, std::string> getInfo();

    void setInfo(std::map<std::string, std::string> info);

    HttpReq(std::string &StrReq);

    std::string getContent();

    void setContent(std::string content);
};


#endif //MNSERVER_HTTPREQ_H
