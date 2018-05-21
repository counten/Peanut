/*
* Author: micle 2017/12/6
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#include "StrUtil.h"

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

std::string StrUtil::suEraseFlSpace(std::string inStr)
{
    inStr = eraseLast(inStr, " \t");
    inStr = eraseLast(inStr, " \n");
    inStr = eraseLast(inStr, " \r");
    inStr = eraseFirst(inStr, " \r");
    inStr = eraseFirst(inStr, " \n");
    inStr = eraseFirst(inStr, " \t");
    return inStr;
}

int StrUtil::suS2i(std::string InStr)
{
    return atoi(InStr.c_str());
}


std::string StrUtil::suI2s(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}

std::vector<std::string> StrUtil::suCutBy(std::string InStr, std::string standard)
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
        std::string tmp = StrUtil::suEraseFlSpace(InStr.substr(0, index));
        result.push_back(tmp);
        InStr = InStr.substr(index + standard.length());
    }
    if (0 != InStr.compare(standard))
    {
        result.push_back(InStr);
    }
    return result;
}

std::string StrUtil::suStr2LowerCase(std::string inStr)
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

std::string StrUtil::suStr2UpperCase(std::string inStr)
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

std::string StrUtil::suGetValueMapKey(std::map<std::string, std:: string> mapIn, std::string key)
{
    std::map<std::string ,std::string >::iterator it;
    it=mapIn.find(key);
    if(it == mapIn.end())
    {
        Log::logWarning("Can not find item in map!");
        return "";
    }
    return it->second;
}

void StrUtil::suPrintVector(std::vector<std::string> vec)
{
    for (std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); it++)
    {
        std::cout << *it << std::endl;
    }
}
