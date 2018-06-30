/*
* Author: micle 2017/12/6
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#ifndef MNSERVER_UTIL_H
#define MNSERVER_UTIL_H

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <cstring>
#include <iconv.h>


// Inner Project
#include "../Log/Log.h"


namespace StrUtil
{
    /**
     * @param InStr;
     * @return OutStr without \r\n;
     * */
    std::string suEraseFlSpace(std::string InStr);

    /**
     * @param string
     * @return int
     * */
    int suS2i(std::string InStr);

    /**
     * @param int
     * @return string
     * */
    std::string suI2s(int i);

    /**
     * @Desc Change string to lowerCase
     * */
    std::string suStr2LowerCase(std::string inStr);

    /**
     * @Desc Change string to upperCase
     * */
    std::string suStr2UpperCase(std::string inStr);


    /**
     * Cut the string by standard into vector;
     * @param cut Standard;
     * @return vector contains sub string;
     * */
    std::vector<std::string> suCutBy(std::string InStr, std::string standard);



    /******* map Opt *************************************************************************/
    /**
     * @Desc get value map to key
     * */
    std::string suGetValueMapKey(std::map<std::string, std:: string>, std::string key);


    /******* Vector Opt *************************************************************************/
    /**
     * @Desc print vector
     * */
    void suPrintVector(std::vector<std::string> vec);
};

#endif //MNSERVER_UTIL_H
