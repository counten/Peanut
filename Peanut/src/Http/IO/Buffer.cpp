/*
* Author: wbq813 2018/3/13
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn
*/

#include "Buffer.h"
#include "../../Log/Log.h"
#include <sys/socket.h>
#include <cstdarg>
#include <new>
#include<sys/uio.h>

/**
 * @Desc read buf from socket;
 * and writerIndex_ equals to the location of content;
 * */
ssize_t Buffer::readFd(int fd, int *savedErrNo)
{
    char extraBuf[65536];
    struct iovec vec[2];
    const size_t writable = writeAbleSize();
    vec[0].iov_base = begin() + wIndex_;
    vec[0].iov_len = writable;
    vec[1].iov_base = extraBuf;
    vec[1].iov_len = sizeof extraBuf;
    const int iovCnt = (writable < sizeof extraBuf) ? 2 : 1;
    // readv和writev函数用于在一次函数调用中读，写多个非连续缓冲区;
    const ssize_t n = readv(fd, vec, iovCnt);

    if (n < 0)
    {
        *savedErrNo = errno;
    }
        // buffer_ is enough to store
    else if (static_cast<size_t>(n) <= writable)
    {
        wIndex_ += n;
    }
        // buffer_ is not enough;
    else
    {
        wIndex_ = buffer_.size();
        append(extraBuf, n - writable);
    }

    return n;
}


/**
 * @Desc format input;
 * */
void Buffer::appendStr(const char *format, ...)
{
    // TODO be more general not
    char extraBuf[2048];
    memset(extraBuf, 0, sizeof extraBuf);
    va_list argList;
    va_start(argList, format);
    vsnprintf(extraBuf, sizeof extraBuf, format, argList);
    va_end(argList);
    append(extraBuf, strlen(extraBuf));
}


/**
 * @return a line from buffer_;
 * */
char* Buffer::getLine()
{
    const char *end = findEOL();
    const char *start = readLoc();
    size_t size;
    // Do not find EOL;
    if (end == nullptr)
    {
        size = writeLoc() -start;
        if(size <1)
        {
            return nullptr;
        }
        retrieve(size);
        char* res;
        try
        {
            res = new char[size + 5];
        }
        catch(const std::bad_alloc &memExp)
        {
            res = nullptr;
            Peanut::logError(memExp.what());
        }
        std::copy(start, start + size, res);
        const char* flag="<end>";
        std::copy(flag,flag+5, res+size);
        return res;
    }
    else
    {
        size = end - start - 1;
        retrieve(size + 2);
        char* res;
        try
        {
            res  = new char[size];
        }
        catch(const std::bad_alloc &memExp)
        {
            res = nullptr;
           Peanut::logError(memExp.what());
        }
        std::copy(start, start + size, res);
        return res;
    }
}


