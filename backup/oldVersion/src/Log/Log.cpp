/*
* Author: micle 2017/12/20
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#include "Log.h"

/**
 * @Desc Format log;
 * */
void logFormat(std::string &tag, std::string inStr)
{
    tag += " ";
    tag += TimeUtil().getLocalTime();
    tag += " | ";
    tag += inStr;
    tag += "\n";
}

void Log::logError(std::string inStr)
{
    std::string outStr = "[ERROR     ]";
    logFormat(outStr, inStr);
    std::cerr << outStr;
    fflush(stdout);
}

void Log::logWarning(std::string inStr)
{
    std::string outStr = "[ WARN     ]";
    logFormat(outStr, inStr);
    std::cout << outStr;
    fflush(stdout);
}

void Log::logInfo(std::string inStr)
{
    std::string outStr = "[  INFO    ]";
    logFormat(outStr, inStr);
    std::cout << outStr;
}

void Log::logSuccess(std::string inStr)
{
    std::string outStr = "[     BINGO]";
    logFormat(outStr, inStr);
    std::cout << outStr;
    fflush(stdout);
}


