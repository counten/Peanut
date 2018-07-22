/*
* Author: wbq813 2017/12/6
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#ifndef MNSERVER_TIMEUTIL_H
#define MNSERVER_TIMEUTIL_H

#include <iostream>
#include <sstream>

namespace Peanut
{
    /**
     * @return current time;
     * */
    static std::string getLocalTime(){
        time_t tt = time(nullptr);
        char szBuf[128] = {0};
        strftime(szBuf, sizeof(szBuf), "%a, %d %b %Y %H:%M:%S", localtime(&tt));
        return szBuf;
    }

    /**
     * @return current GMT time;
     * */
    static std::string getGMTime(){
        time_t t = time(nullptr);
        char szBuf[128] = {0};
        strftime(szBuf, sizeof(szBuf), "%a, %d %b %y %H:%M:%S GMT", gmtime(&t));
        return szBuf;
    }

    /**
     * @return timestamps
     * */
    static std::string getTimestamps(){
        time_t curtime = time(NULL);
        std::stringstream ss;
        ss << curtime;
        return ss.str();
    }
};


#endif //MNSERVER_TIMEUTIL_H
