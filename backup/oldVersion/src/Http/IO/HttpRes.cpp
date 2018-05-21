/*
* Author: micle 2017/12/6
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#include <cstring>
#include "HttpRes.h"

int HttpRes::format(unsigned char *send_buf)
{
    std::string str = getProtocal();
    str += " ";
    str += StrUtil::suI2s(getStatus());
    str += "\r\nDate: ";
    str += getDate();
    str += "\r\nServer: ";
    str += getServer();
    str += "\r\nContent-Type: ";
    str += getCType();
    if (0 != getAllows().compare(NONE_INIT))
    {
        str += "\r\nAllow: ";
        str += getAllows();
    }
    str += "\r\nContent-Length: ";
    str += StrUtil::suI2s(getCLen());
    str += "\r\n\r\n";


    if(0 == getStrContent().compare(NONE_INIT))
    { // content store special file;
        const char *strBuf = str.c_str();
        int index = strlen(strBuf);
        memcpy(send_buf, strBuf, index);
        memcpy(send_buf + index, content, cLen);
        return index + cLen;
    }
    else
    { // strContent store text;
        str += getStrContent();
        const char *strBuf = str.c_str();
        int index = strlen(strBuf);
        memcpy(send_buf, strBuf, index);
        return index;
    }
}

HttpRes::HttpRes()
{
    setProtocal(HTTP_V1);
    setStatus(RES_OK);
    setServer(SERVER);
    setCType(CTYPE_TEXT_UTF8);
    setDate(TimeUtil().getGMTime());
    unsigned char *str;
    setContent(str);
    setAllows(NONE_INIT);
    setCLen(0);
    setStrContent(NONE_INIT);
}

std::string HttpRes::getProtocal()
{
    return protocal;
}

void HttpRes::setProtocal(std::string protocal)
{
    HttpRes::protocal = protocal;
}

int HttpRes::getStatus()
{
    return status;
}

void HttpRes::setStatus(int status)
{
    HttpRes::status = status;
}

std::string HttpRes::getDate()
{
    return date;
}

void HttpRes::setDate(std::string date)
{
    HttpRes::date = date;
}

std::string HttpRes::getServer()
{
    return server;
}

void HttpRes::setServer(std::string server)
{
    HttpRes::server = server;
}

std::string HttpRes::getCType()
{
    return cType;
}

void HttpRes::setCType(std::string cType)
{
    HttpRes::cType = cType;
}

std::string HttpRes::getAllows()
{
    return allows;
}

void HttpRes::setAllows(std::string allows)
{
    HttpRes::allows = allows;
}

int HttpRes::getCLen()
{
    return cLen;
}

void HttpRes::setCLen(int cLen)
{
    HttpRes::cLen = cLen;
}

const unsigned char *HttpRes::getContent()
{
    return content;
}

void HttpRes::setContent(unsigned char *con)
{
//    memset(HttpRes::content, '\0', sizeof(HttpRes::content));
//    memcpy(HttpRes::content, con, getCLen());
    HttpRes::content = con;
}

std::string HttpRes::getStrContent() const {
    return strContent;
}

void HttpRes::setStrContent(std::string strContent) {
    HttpRes::strContent = strContent;
}

