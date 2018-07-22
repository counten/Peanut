/*
* Author: wbq813 2017/12/12
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#include "ReqInfo.h"
#include "../../Util/StrUtil.h"
#include "../../Util/EdCode.h"

// Inner Project


void ReqInfo::package(std::string clientIP, std::string url)
{
    int loc = url.find_first_of('?');
    if(loc != -1)
    {
        url = url.substr(loc + 1);
        str2Map(url, ReqInfo::urlParams_);
    }
    this->content_ = "";
    this->clientIP_ = clientIP;
};

void ReqInfo::package(std::string clientIP, std::string url, std::string content) {
    this->content_ = Peanut::UrlDecode(content);
    this->clientIP_ = clientIP;
    int loc = url.find_first_of('?');
    if(loc != -1)
    {
        url = url.substr(loc + 1);
        str2Map(url, ReqInfo::urlParams_);
    }
}

void ReqInfo::reset()
{
    content_.clear();
    clientIP_.clear();
    urlParams_.clear();
}

int ReqInfo::str2Map(std::string inStr, std::map<std::string, std:: string> & map)
{
    // TODO cut by ‘&’ or '=', will be error while the content contains '&' and '='
    // '&'的数量是'='数量-1
    std::vector <std::string> params = Peanut::cutBy(inStr, "&");
    std::vector <std::string> tmp;
    for (std::vector<std::string>::iterator it = params.begin(); it != params.end(); it++)
    {
        tmp.empty();
        tmp = Peanut::cutTo2(*it, "=");
        map.insert(
                std::pair<std::string, std::string>(tmp[0], tmp[1])
        );
    }
    return 0;
};

std::map<std::string, std::string> ReqInfo::getUrlParams()
{
    return urlParams_;
}

std::string ReqInfo::getUrlParam(std::string key)
{
    return Peanut::getValueMapKey(ReqInfo::urlParams_, key);
}

std::string ReqInfo::getContent() {
    return content_;
}

std::string ReqInfo::getClientIP() const
{
    return clientIP_;
}


