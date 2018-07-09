/*
* Author: micle 2017/12/6
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#include "StrUtil.h"

#include <sstream>
#include <cstring>

// Inner Project
#include "../Log/Log.h"

std::string eraseLast(std::string inStr, std::string stand)
{
    size_t n = inStr.find_last_not_of(stand);
    if (n != std::string::npos)
    {
        inStr.erase(n + 1, inStr.size() - n);
    }
    return inStr;
}

std::string eraseFirst(std::string inStr, std::string stand)
{
    size_t n = inStr.find_first_not_of(stand);
    if (n != std::string::npos)
    {
        inStr.erase(0, n);
    }
    return inStr;
}

std::string Peanut::eraseFlSpace(std::string inStr)
{
    inStr = eraseLast(inStr, " \t");
    inStr = eraseLast(inStr, " \n");
    inStr = eraseLast(inStr, " \r");
    inStr = eraseFirst(inStr, " \r");
    inStr = eraseFirst(inStr, " \n");
    inStr = eraseFirst(inStr, " \t");
    return inStr;
}

int Peanut::S2i(std::string InStr)
{
    return atoi(InStr.c_str());
}


std::string Peanut::I2s(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}


std::string Peanut::str2LowerCase(std::string inStr)
{
    for (int i = 0; i < inStr.size(); i++)
    {
        if (inStr[i] >= 'A' && inStr[i] <= 'Z')
        {
            inStr[i] += ('a' - 'A');
        }
    }
    return inStr;
}

std::string Peanut::str2UpperCase(std::string inStr)
{
    for (int i = 0; i < inStr.size(); i++)
    {
        if (inStr[i] >= 'a' && inStr[i] <= 'z')
        {
            inStr[i] += ('A' - 'a');
        }
    }
    return inStr;
}

/**
 * @Desc replace all the a to b in str;
 * */
std::string  Peanut::replaceAll(std::string str, std::string old_value, std::string new_value)
{
    int loc =0;
    while(true)
    {
        loc = str.find(old_value, loc);
        if(loc > 0)
        {
            str.replace(loc,old_value.length(),new_value);
            loc += new_value.length();
        }
        else{
            break;
        }
    }
    return str;
}

/**
 * @Desc add quotation, if the strin contains the quotation replace to two quotation;
 * */
std::string Peanut::addQuo(std::string inStr, std::string quotation) {
    inStr = replaceAll(inStr, quotation, quotation+quotation);
    inStr = quotation + inStr +quotation;
    return inStr;
}

std::string Peanut::addQuo(std::string inStr) {
    std::string quo= "'";
    inStr = replaceAll(inStr, quo, quo+quo);
    inStr = quo + inStr +quo;
    return inStr;
}

std::vector<std::string> Peanut::cutBy(std::string InStr, std::string standard)
{
    std::vector<std::string> result;
    int index;

    while ((index = InStr.find(standard)) >= 0)
    {
        // Deal with multi standard together like "\n\n";
        if (index == 0)
        {
            InStr = InStr.substr(index + 1);
            continue;
        }
        std::string tmp = Peanut::eraseFlSpace(InStr.substr(0, index));
        result.push_back(tmp);
        InStr = InStr.substr(index + standard.length());
    }
    if (0 != InStr.compare(standard))
    {
        result.push_back(InStr);
    }
    return result;
}

std::vector<std::string> Peanut::cutTo2(std::string InStr, std::string standard)
{
    std::vector<std::string> result;
    int index = InStr.find(standard);

    if (index >= 0)
    {
        std::string tmp = Peanut::eraseFlSpace(InStr.substr(0, index));
        result.push_back(tmp);
        InStr = InStr.substr(index + standard.length());
        result.push_back(Peanut::eraseFlSpace(InStr));
    }
    return result;
}

std::string Peanut::getValueMapKey(std::map<std::string, std::string> mapIn, std::string key)
{
    std::map<std::string ,std::string >::iterator it;
    it=mapIn.find(key);
    if(it == mapIn.end())
    {
        logWarning("Can not find item in map!");
        return "";
    }
    return it->second;
}

void Peanut::printVector(std::vector<std::string> vec)
{
    for (std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); it++)
    {
        std::cout << *it << std::endl;
    }
}
