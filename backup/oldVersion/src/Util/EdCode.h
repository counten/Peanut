/*
* Author: micle 2018/3/7
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn 
*/


#ifndef MNSERVER_EDCODE_H
#define MNSERVER_EDCODE_H

#include <iostream>
#include "CodeConverter.h"

namespace EdCode
{
    std::string Url2StrGB2312(std::string str);

    std::string Url2StrUTF8(std::string instr);
}

#endif //MNSERVER_EDCODE_H
