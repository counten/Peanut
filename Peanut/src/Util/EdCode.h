/*
* Author: wbq813 2018/3/7
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn 
*/


#ifndef MNSERVER_EDCODE_H
#define MNSERVER_EDCODE_H

#include <iostream>

namespace Peanut
{
    char Char2Int(char ch);

    char Str2Bin(char *str);

    std::string UrlDecode(std::string str);

/**
 * @Desc Convert one charset to another
 * */
    size_t convert(const char *fCharset, const char *tCharset,
                   char *inbuf, int inlen, char *outbuf, int outlen);

    std::string Url2StrGB2312(std::string str);

    std::string Url2StrUTF8(std::string instr);
}

#endif //MNSERVER_EDCODE_H
