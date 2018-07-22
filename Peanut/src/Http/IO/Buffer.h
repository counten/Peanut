/*
* Author: wbq813 2018/3/13
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn
*/

#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <vector>
#include <cstdio>
#include <cstddef>
#include <cerrno>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <iostream>

class Buffer
{
private:

    std::vector<char> buffer_;
    size_t rIndex_;
    size_t wIndex_;

    char *begin()
    {
        return &*buffer_.begin();
    }

    const char *begin() const
    {
        return &*buffer_.begin();
    }


public:

    explicit Buffer(size_t initialSize = 1024):
            buffer_(initialSize)
    {}

    size_t readAbleSize() const
    {
        return wIndex_ - rIndex_;
    }

    size_t writeAbleSize() const
    {
        return buffer_.size() - wIndex_;
    }

    /** read from here*/
    const char *readLoc() const
    {
        return begin() + rIndex_;
    }

    /** Location to begin write;*/
    const char *writeLoc() const
    {
        return begin() + wIndex_;
    }

    const char *findEOL() const
    {
        const void *eol = memchr(readLoc(), '\n', readAbleSize());
        return static_cast<const char *>(eol);
    }

    const char *findCRLF() const
    {
        const char kCRLF[] = "\r\n";
        const char *crlf = std::search(readLoc(), writeLoc(), kCRLF, kCRLF + 2);
        return crlf == writeLoc() ? NULL : crlf;
    }

    void retrieveAll()
    {
        rIndex_ = 0;
        wIndex_ = 0;
    }

    void retrieve(size_t len)
    {
        if (len < readAbleSize())
        {
            rIndex_ += len;
        } else
        {
            retrieveAll();
        }
    }

    /**
     * @Desc add string to buffer_
     * and move the writerIndex_ to correct location;
     * */
        void append(const char *data, size_t len)
        {
            if (writeAbleSize() < len)
            {
                if (writeAbleSize() + rIndex_ < len )
                {
                    // Re malloc store space;
                    buffer_.resize(wIndex_ + len);
                }
                else
                {
                    std::copy(begin() + rIndex_, begin() + wIndex_, begin());
                    rIndex_ = 0;
                    wIndex_ = rIndex_ + readAbleSize();
                }
            }
            std::copy(data, data + len, begin() + wIndex_);
            wIndex_ += len;
        }

/**
 * @Desc read buf from socket;
 * */
    ssize_t readFd(int fd, int *savedErrNo);

/**
 * @Desc format input;
 * */
    void appendStr(const char *format, ...);

/**
 * @return a line from buffer_;
 * */
    char* getLine();

};

#endif
