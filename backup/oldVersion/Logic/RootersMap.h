/*
* Author: micle 2018/01/12
* Env: ubuntu 1604, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/


#ifndef MNSERVER_MNBASE_H
#define MNSERVER_MNBASE_H

#include <iostream>
#include <map>

// Inner Project
#include "../src/Http/Dispatcher/MnRequest.h"

typedef std::string (*pController)(MnRequest);

extern std::map<std::string, pController> strControllerMap;

#include "Controller/blogController.h"

void registerController();

#endif //MNSERVER_MNBASE_H
