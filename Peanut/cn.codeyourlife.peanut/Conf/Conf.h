/*
* Author: micle 2017/12/6
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn 
*/

#ifndef MNSERVER_READCONF_H
#define MNSERVER_READCONF_H

#include <iostream>
#include <fstream>



namespace Peanut
{
    /**
     * @param vector to store confValue;
     * @return 0:success, 1:failed;
     * */
    int readConfAll();


    /**
     * @param module
     * @param key
     * @return value map to key
     * */
    std::string getValue(std::string module, std::string key);
};

#endif //MNSERVER_READCONF_H
