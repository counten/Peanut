/*
* Author: micle 2018/3/7
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn 
*/

#include "EdCode.h"
#include <iconv.h>
#include <cstring>


char Peanut::Char2Int(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return (char) (ch - '0');
    }

    if (ch >= 'a' && ch <= 'f')
    {
        return (char) (ch - 'a' + 10);
    }

    if (ch >= 'A' && ch <= 'F')
    {
        return (char) (ch - 'A' + 10);
    }
    return -1;
}

char Peanut::Str2Bin(char *str)
{
    char tempWord[2];
    char chn;
    tempWord[0] = Char2Int(str[0]);                                //make the B to 11 -- 00001011
    tempWord[1] = Char2Int(str[1]);                                //make the 0 to 0  -- 00000000
    chn = (tempWord[0] << 4) | tempWord[1];                //to change the BO to 10110000
    return chn;
}

std::string Peanut::UrlDecode(std::string str)
{
    std::string output = "";
    char tmp[2];
    int i = 0;
    int len = str.length();

    while (i < len)
    {
        if (str[i] == '%')
        {
            tmp[0] = str[i + 1];
            tmp[1] = str[i + 2];
            output += Str2Bin(tmp);
            i = i + 3;
        } else if (str[i] == '+')
        {
            output += ' ';
            i++;
        } else
        {
            output += str[i];
            i++;
        }
    }

    return output;
}

/**
 * @Desc Convert one charset to another
 * */
size_t Peanut::convert(const char *fCharset, const char *tCharset,
                       char *inbuf, int inlen, char *outbuf, int outlen)
{
    iconv_t cd = iconv_open(tCharset, fCharset);
    char **pin = &inbuf;
    char **pout = &outbuf;

    memset(outbuf, 0, outlen);
    size_t res = iconv(cd, pin, (size_t *) &inlen, pout, (size_t *) &outlen);
    iconv_close(cd);
    return res;
}


std::string Peanut::Url2StrGB2312(std::string str)
{
    return UrlDecode(str);
}

std::string Peanut::Url2StrUTF8(std::string instr)
{
    std::string input = UrlDecode(instr);

    char *inBuf = const_cast<char *>(input.c_str());
    const int inLen = strlen(inBuf);
    const int outlen = instr.length();
    char output[outlen];

    convert("utf-8", "gb2312", inBuf, inLen, output, outlen);

    return output;
}