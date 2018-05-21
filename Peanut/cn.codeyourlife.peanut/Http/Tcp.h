/*
* Author: micle 2018/3/11
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn 
*/
#ifndef PEANUT_TCP_H
#define PEANUT_TCP_H

#include <sys/socket.h>

namespace Peanut
{

    /**
     * @Desc Create socket and catch exception;
     * */
    int Socket(int domain, int type, int protocol);

    /**
     * @Desc Set port reuse and catch exception;
     * */
    int SetSockOpt(int s, int level, int optName, const void *optVal, int optLen);

    /**
     * @Desc Bind and catch exception;
     * */
    int Bind(int sockFd, sockaddr *myAdd, int addLen);


    /**
     * @Desc Listen and catch exception;
     * */
    int Listen(int s, int backlog);


    /**
     * @Desc Whole Process of TCP；
     * */
    int OpenListenFd(int port);

}

#endif //PEANUT_TCP_H
