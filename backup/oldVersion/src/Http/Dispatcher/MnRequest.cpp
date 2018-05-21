/*
* Author: micle 2017/12/12
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#include "MnRequest.h"

MnRequest::MnRequest()
{

};

int MnRequest::str2Map(std::string inStr, std::map<std::string, std:: string> & map)
{
    std::vector <std::string> params = StrUtil::suCutBy(inStr,"&");
    std::vector <std::string> tmp;
    for (std::vector<std::string>::iterator it = params.begin(); it != params.end(); it++)
    {
        tmp.empty();
        tmp = StrUtil::suCutBy(*it, "=");
        map.insert(
                std::pair<std::string, std::string>(tmp[0], tmp[1])
        );
    }
    return 0;
};

MnRequest::MnRequest(std::string url)
{
    int loc = url.find_first_of('?');
    if(loc != -1)
    {
        url = url.substr(loc + 1);
        str2Map(url, MnRequest::urlParams);
    }
    this->content = "";
    return ;
};


MnRequest::MnRequest(std::string url, std::string content) {
    std::cout << "\nloc 3: " << url << " : " << content;
    this->content = content;
    int loc = url.find_first_of('?');
    if(loc != -1)
    {
        url = url.substr(loc + 1);
        str2Map(url, MnRequest::urlParams);
    }
    std::cout << "\nloc 4: " << url << " : " << this->content;
    return ;
}

std::map<std::string, std::string> MnRequest::getUrlParams()
{
    return urlParams;
}

std::string MnRequest::getUrlParam(std::string key)
{
    return StrUtil::suGetValueMapKey(MnRequest::urlParams, key);
}

std::string MnRequest::getContent() {
    return content;
}


