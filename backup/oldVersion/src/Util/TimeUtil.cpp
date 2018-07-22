/*
* Author: micle 2017/12/6
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#include "TimeUtil.h"

TimeUtil::TimeUtil() {}

std::string TimeUtil::getLocalTime()
{
    time_t tt = time(NULL);
    char szBuf[128] = {0};
    strftime(szBuf, sizeof(szBuf), "%a, %d %b %Y %H:%M:%S", localtime(&tt));
    return szBuf;
}

std::string TimeUtil::getGMTime()
{
    time_t t = time(NULL);
    char szBuf[128] = {0};
    strftime(szBuf, sizeof(szBuf), "%a, %d %b %y %H:%M:%S GMT", gmtime(&t));
    return szBuf;
}
