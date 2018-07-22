/*
* Author: micle 2017/12/12
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#ifndef MNSERVER_MNREQUEST_H
#define MNSERVER_MNREQUEST_H

#include <map>
#include <vector>

// Inner Project
#include "../../Log/Log.h"
#include "../../Util/StrUtil.h"

class MnRequest {
private:
    std::map <std::string, std::string> urlParams;

    std::string content;

public:
    MnRequest();

    // Constructor for GET method only deal url;
    MnRequest(std::string url);

    // Constructor for POST and PUT deal with content
    MnRequest(std::string url, std::string content);

    /**
     * @Desc inStr should contains '&' and '=' like 'user_email=1452634758&user_password=123456';
     * @return map
     * */
    int str2Map(std::string inStr, std::map<std::string, std:: string> & map);

    /**
     * @return params;
     * */
    std::map<std::string, std::string> getUrlParams();

    /**
     * @param key to the map;
     * @return value of request params;
     * */
    std::string getUrlParam(std::string key);

    std::string getContent();
};


#endif //MNSERVER_MNREQUEST_H
