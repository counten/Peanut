/*
* Author: micle 2017/12/20
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#ifndef MNSERVER_LOG_H
#define MNSERVER_LOG_H

#include <iostream>
#include "../Util/TimeUtil.h"


namespace Log
{

    void logError(std::string inStr);

    void logWarning(std::string inStr);

    void logInfo(std::string inStr);

    void logSuccess(std::string inStr);

};


#endif //MNSERVER_LOG_H
