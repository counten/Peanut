/*
* Author: wbq813 2017/12/6
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#ifndef MNSERVER_UTIL_H
#define MNSERVER_UTIL_H

#include <iostream>

#include <vector>
#include <map>



namespace Peanut
{
    /**
     * @param InStr;
     * @return OutStr without \r\n;
     * */
    std::string eraseFlSpace(std::string InStr);

    /**
     * @param string
     * @return int
     * */
    int S2i(std::string InStr);

    /**
     * @param int
     * @return string
     * */
    std::string I2s(int i);

    /**
     * @Desc Change string to lowerCase
     * */
    std::string str2LowerCase(std::string inStr);

    /**
     * @Desc Change string to upperCase
     * */
    std::string str2UpperCase(std::string inStr);


    /**
     * @Desc replace all the a to b in str;
     * */
    std::string  replaceAll(std::string str, std::string old_value, std::string new_value);

    /**
     * Cut the string by standard into vector;
     * @param cut Standard;
     * @return vector contains sub string;
     * */
    std::vector<std::string> cutBy(std::string InStr, std::string standard);

    std::vector<std::string> cutTo2(std::string InStr, std::string standard);

    /**
     * @Desc add quotation, if the strin contains the quotation replace to two quotation;
     * */
    std::string addQuo(std::string, std::string);

    std::string addQuo(std::string);

    /******* map Opt *************************************************************************/
    /**
     * @Desc get value map to key
     * */
    std::string getValueMapKey(std::map<std::string, std::string>, std::string key);


    /******* Vector Opt *************************************************************************/
    /**
     * @Desc print vector
     * */
    void printVector(std::vector<std::string> vec);
};

#endif //MNSERVER_UTIL_H
