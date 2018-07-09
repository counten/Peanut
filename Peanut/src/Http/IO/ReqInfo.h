/*
* Author: micle 2017/12/12
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#ifndef MNSERVER_MNREQUEST_H
#define MNSERVER_MNREQUEST_H

#include <map>
#include <vector>


class ReqInfo {
private:
    std::map <std::string, std::string> urlParams_;

    std::string content_;

    std::string clientIP_;

public:

    // Constructor for GET method only deal url;
    void package(std::string clientIP, std::string url);

    // Constructor for POST and PUT deal with content_
    void package(std::string clientIP, std::string url, std::string content);

    void reset();

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

    std::string getClientIP() const;

};


#endif //MNSERVER_MNREQUEST_H
