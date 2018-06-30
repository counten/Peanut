/*
* Author: micle 2018/3/1
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn 
*/

#include "RootersMap.h"

std::map<std::string, pController> strControllerMap;

// Register URL here !
void registerController()
{
    // blog related API
    strControllerMap["/blogs"] = &blogsController;
    strControllerMap["/detail"] = &detailController;

    // User related API
}