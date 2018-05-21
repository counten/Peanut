/*
* Author: micle 2017/12/6
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#ifndef MNSERVER_TIMEUTIL_H
#define MNSERVER_TIMEUTIL_H

#include <iostream>
#include <time.h>

// Inner Project
#include "StrUtil.h"

class TimeUtil
{
public:

    TimeUtil();

    /**
     * @return current time;
     * */
    std::string getLocalTime();

    /**
     * @return current GMT time;
     * */
    std::string getGMTime();
};


#endif //MNSERVER_TIMEUTIL_H
