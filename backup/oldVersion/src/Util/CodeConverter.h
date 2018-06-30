/*
* Author: micle 2018/3/7
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn 
*/


#ifndef MNSERVER_CODECONVERTER_H
#define MNSERVER_CODECONVERTER_H

#include <iconv.h>
#include <cstring>


/**
 * @Desc use like this;
 *
 *  const int outlen = instr.length();
    char output[outlen];
    CodeConverter cc = CodeConverter("utf-8", "gb2312");
    cc.convert((char *) input.c_str(), strlen(input.c_str()), output, outlen);
 * */
class CodeConverter
{
private:
    iconv_t cd;

public:
    CodeConverter(const char *from_charset, const char *to_charset)
    {
        cd = iconv_open(to_charset, from_charset);
    }

    ~CodeConverter()
    {
        iconv_close(cd);
    }

    int convert(char *inbuf, int inlen, char *outbuf, int outlen)
    {
        char **pin = &inbuf;
        char **pout = &outbuf;

        memset(outbuf, 0, outlen);
        return iconv(cd, pin, (size_t *) &inlen, pout, (size_t *) &outlen);
    }
};

#endif //MNSERVER_CODECONVERTER_H
