/*
* Author: micle 2018/3/10
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn 
*/


#ifndef PROJECT_LOG_NEW_H
#define PROJECT_LOG_NEW_H


#include <pthread.h>
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include "../Util/TimeUtil.h"


namespace Peanut
{

static void log()
{
    printf("\n");
} // 递归终止条件。这是必需的。

template<typename Type, typename... Types>
static void log(const Type& arg, const Types&... args)
{
    std::cout << arg;
    log(args...);
}

template<typename Type, typename... Types>
void logSuccess(const Type& arg, const Types&... args)
{
    std::cout<< "[   Bingo] "+ getLocalTime() + " | " +arg;
    log(args...);
    fflush(stdout);
}

template<typename Type, typename... Types>
void logInfo(const Type& arg, const Types&... args)
{
    std::cout<< "[  Info  ] "+ getLocalTime() + " | " + arg;
    log(args...);
}


#define logWarning(arg, args...)lWarning(pthread_self(), __FILE__, __LINE__, __FUNCTION__, arg, ##args)
template<typename Type, typename... Types>
void lWarning(pthread_t tid, const char *fileName, int lineNum, const char *func, const Type& arg, const Types&... args)
{
    std::cout<< "[ Warn   ] "+ getLocalTime() + " | " + arg;
    printf("\n%lu %s:%d | %s\n", tid, fileName, lineNum, func);
    log(args...);
    fflush(stdout);
}

#define logError(arg, args...)lError(pthread_self(), __FILE__, __LINE__, __FUNCTION__, arg, ##args)
template<typename Type, typename... Types>
void lError(pthread_t tid, const char *fileName, int lineNum, const char *func, const Type& arg, const Types&... args)
{
    std::cout<< "[Error   ] "+ getLocalTime() + " | " + arg;
    printf("\n%lu %s:%d | %s \n", tid, fileName, lineNum, func);
    log(args...);
    fflush(stdout);
}
}


#endif //PROJECT_LOG_NEW_H
