/*
* Author: micle 2017/12/14
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#include "HttpReq.h"

HttpReq::HttpReq(std::string &StrReq)
{
    StrReq = StrUtil::suEraseFlSpace(StrReq);
    std::vector<std::string> allInfo = StrUtil::suCutBy(StrReq, "\n");

    // deal first line;
    std::vector<std::string> firstLine = StrUtil::suCutBy(allInfo[0], " ");
    setMethod(StrUtil::suStr2UpperCase(firstLine[0]));
    setUrl(firstLine[1]);
    setProtocal(firstLine[2]);

//    StrUtil::suPrintVector(allInfo);
    // deal others;
    std::vector<std::string> tmp;
    std::map<std::string, std::string> Info;

    // Put all the data into map except last one(content)
    for (std::vector<std::string>::iterator it = allInfo.begin() + 1; it != allInfo.end() - 1; it++)
    {
        tmp.empty();
        std::string tmpStr = StrUtil::suEraseFlSpace(*it);
        tmp = StrUtil::suCutBy(tmpStr, ": ");
        if (tmp.size() > 1)
        {
            Info.insert(std::pair<std::string, std::string>(StrUtil::suStr2UpperCase(tmp[0]),tmp[1]));
        }
        else
        {
            Info.insert(std::pair<std::string, std::string>(StrUtil::suStr2UpperCase(tmp[0]),""));
        }
    }
    // If Content-length > 0; get content;
    std::string Content_length = StrUtil::suGetValueMapKey(Info, "CONTENT-LENGTH");
    if ((Content_length.length() > 0 && StrUtil::suS2i(Content_length) > 0) )
    {
        setContent(StrUtil::suEraseFlSpace(*(allInfo.end() - 1)));
    } else
    {
        setContent("");
    }
    setInfo(Info);
}

std::string HttpReq::getMethod()
{
    return method;
}

void HttpReq::setMethod(std::string method)
{
    HttpReq::method = method;
}

std::string HttpReq::getUrl()
{
    return url;
}

void HttpReq::setUrl(std::string url)
{
    HttpReq::url = url;
}

std::string HttpReq::getProtocal()
{
    return protocal;
}

void HttpReq::setProtocal(std::string protocal)
{
    HttpReq::protocal = protocal;
}

std::map<std::string, std::string> HttpReq::getInfo()
{
    return info;
}

void HttpReq::setInfo(std::map<std::string, std::string> info)
{
    HttpReq::info = info;
}

std::string HttpReq::getContent(){
    return content;
}

void HttpReq::setContent(std::string content) {
    HttpReq::content = content;
}
