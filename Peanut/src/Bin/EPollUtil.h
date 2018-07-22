/*
* Author: wbq813 2018/3/13
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn
*/

#ifndef _EPOLL_ULTI_H_
#define _EPOLL_ULTI_H_


#include <sys/epoll.h>

namespace Peanut {

    void removeFd(int epollFd, int fd);

    void modFd(int ePollFd, int fd, int ev, bool oneShot);

    void addFd(int ePollFd, int fd, bool one_shot);

    int EPollWait(int ePfd, epoll_event *events, int maxEvents, int timeout);

    int EPollCreate(int size);

}

#endif
