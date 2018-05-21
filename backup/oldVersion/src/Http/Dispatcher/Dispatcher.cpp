/*
* Author: micle 2017/12/12
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#include <cstring>
#include "Dispatcher.h"


Dispatcher::Dispatcher(std::string Req)
{
    setRequest(Req);
    HttpReq httpReq(Req);
    Log::logSuccess(httpReq.getMethod() + " \" " + httpReq.getUrl() + " \" " + httpReq.getProtocal());
    setURL(httpReq.getUrl());
    setMethod(httpReq.getMethod());
    setProtocal(httpReq.getProtocal());
    setContent(httpReq.getContent());
}

int Dispatcher::getRes(unsigned char *send_buf)
{
    HttpRes httpRes;
    std::string url = getURL();
    std::string method = getMethod();
    // Methods
    if (0 == method.compare(METHOD_GET))
    {
        url2Controller(url, httpRes);
    }
    else if (0 == method.compare(METHOD_POST))
    {
        url2Controller(url, getContent(), httpRes);
    }
    else if (0 == method.compare(METHOD_PUT))
    {
        url2Controller(url, getContent(), httpRes);
    }
    else if (0 == method.compare(METHOD_DELETE))
    {

    }
    else if (0 == method.compare(METHOD_HEAD))
    {
        url2Controller(url, httpRes);
        httpRes.setStrContent("");
    }
    else if (0 == method.compare(METHOD_TRACE))
    {
        // TODO result have problem about pointer
        std::string recv = getRequest();
        httpRes.setCLen(recv.size());
        httpRes.setStrContent(recv);
    }
    else if (0 == method.compare(METHOD_OPTIONS))
    {
        httpRes.setAllows("GET, POST, PUT, DELETE, HEAD, TRACE, OPTIONS");
        httpRes.setCLen(0);
    }
    else
    {
        // TODO 500 unSupport method
    }

    return httpRes.format(send_buf);
}

int Dispatcher::url2Controller(std::string url, HttpRes &httpRes)
{
    // url without params;
    std::string pureUrl = url.substr(0, url.find_first_of('?'));
    if (strControllerMap.count(pureUrl))
    {
        // Get params in url;
        MnRequest mnRequest(url);
        std::string result = (*strControllerMap[pureUrl])(mnRequest);
        httpRes.setCLen(result.size());
        httpRes.setStrContent(result);
    }
    else
    {     // static request
        url2File(pureUrl, httpRes);
    }
    return 0;
}

int Dispatcher::url2Controller(std::string url, std::string content, HttpRes &httpRes)
{
    std::cout << "\nloc 1";
    if (strControllerMap.count(url))
    {
        std::cout << "\nloc 2: "<< content;
        // Get params in url;
        MnRequest mnRequest(url, content);
        std::cout << "\nloc 5";
        std::string result = (*strControllerMap[url])(mnRequest);
        std::cout << "\nloc 6";
        httpRes.setCLen(result.size());
        httpRes.setStrContent(result);
    }
    else
    {   // 404 Interface not found
        // TODO 404
    }
    return 0;
}

void Dispatcher::url2File(std::string url, HttpRes &httpRes)
{
    FileUtil fileUtil;
    Conf conf;
    int fileSize = StrUtil::suS2i(conf.getValue(CFG_STATIC, CFG_STATIC_FILESIZE));
    unsigned char content[fileSize + 1] = {0};
    int cLen;
    std::string filePath;

    // end with "/", try to open x/index.html;
    int loc = url.find_last_of("/");
    int len = url.length();
    if (0 == url.compare("/") || loc == len)
    {
        filePath = url + "index.html";
    } else {
        filePath = url;
    }

    // drop the start "/"
    if (0 == filePath.find_first_of("/"))
    {
        filePath = filePath.substr(1);
    }
    // Open File
    std::string basePath = conf.getValue(CFG_STATIC, CFG_STATIC_DIR);
    cLen = fileUtil.get_file_disk(basePath + filePath, content);
    if (cLen <= 0)
    { // Can not find file return 404;
        filePath = "404.html";
        cLen = fileUtil.get_file_disk(basePath + filePath, content);
        httpRes.setStatus(FILE_NOT_FOUND);
    }
    httpRes.setCLen(cLen);
    httpRes.setContent(content);
    url2CType(filePath, httpRes);
}

void Dispatcher::url2CType(std::string url, HttpRes &httpRes)
{
    int loc = url.find_last_of(".");
    if (-1 != loc)
    {
        std::string endFix = url.substr(loc + 1);
        endFix = StrUtil::suStr2LowerCase(endFix);
        std::string cType = StrUtil::suGetValueMapKey(resMap, endFix);
        httpRes.setCType(cType);
    }
    return;
}

const std::string Dispatcher::getURL()
{
    return URL;
}

void Dispatcher::setURL(std::string URL)
{
    Dispatcher::URL = URL;
}

std::string Dispatcher::getMethod()
{
    return method;
}

void Dispatcher::setMethod(std::string method)
{
    Dispatcher::method = method;
}

std::string Dispatcher::getProtocal()
{
    return protocal;
}

void Dispatcher::setProtocal(const std::string &protocal)
{
    Dispatcher::protocal = protocal;
}

std::string Dispatcher::getRequest() {
    return request;
}

void Dispatcher::setRequest(std::string request) {
    Dispatcher::request = request;
}

std::string Dispatcher::getContent(){
    return content;
}

void Dispatcher::setContent(std::string content) {
    Dispatcher::content = content;
}




