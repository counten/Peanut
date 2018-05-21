/*
* Author: micle 2018/01/25
* Env: debian 9, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#ifndef MNSERVER_FRAME_H
#define MNSERVER_FRAME_H

// just support from linux
#include<netinet/in.h>
#include<unistd.h>   //for fork and read
#include<sys/types.h>   //for socket
#include<sys/socket.h>  //for socket
#include<arpa/inet.h>
#include <signal.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <memory.h>

#include "../Log/Log.h"
#include "../Conf/Conf.h"
#include "../Http/Dispatcher/Dispatcher.h"
#include "ThreadPool.h"


namespace Frame
{

/**
 * @param sock after listen;
 * @Desc Use multiProcess to deal different request;
 * */
    void ProcessFrame(int sock);


/**
 * @param sock after listen;
 * @Desc Use epoll to deal different request;
 * */

    int EpollThreadFrame(int sock);
}

#endif //MNSERVER_FRAME_H
