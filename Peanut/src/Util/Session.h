/*
* Author: wbq813 2018/3/21
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn 
*/


#ifndef PEANUT_SESSION_H
#define PEANUT_SESSION_H

#include <iostream>
#include "../Conf/Defination.h"

StringHash _sessionMap;
bool _isSessionOn = false;

namespace Peanut
{

    /**
     * @Desc addSession
    * */
    bool addSession(std::string clientIp, std::string name, std::string value)
    {
        if(clientIp.length() < 7)
        {
            return false;
        }
        if(!_isSessionOn)
        {
            _isSessionOn = true;
        }
        return _sessionMap.Hash(clientIp+name, value);
    }

/**
 * @Desc getSession
* */
    std::string getSession(std::string clientIp, std::string key)
    {

        return _sessionMap.Hashed(clientIp+key);
    }

}
#endif //PEANUT_SESSION_H
