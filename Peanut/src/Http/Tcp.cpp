/*
* Author: wbq813 2018/3/11
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn 
*/

#include "Tcp.h"

#include <cstring>
#include <netinet/in.h>

// Inner project
#include "../Log/Log.h"
#include "../Util/StrUtil.h"
#include "../Conf/Conf.h"
#include "../Conf/Defination.h"


int Peanut::Socket(int domain, int type, int protocol)
{
    int rc = socket(domain, type, protocol);
    if (rc  < 0)
    {
        logError("Socket error");
    }
    return rc;
}

int Peanut::SetSockOpt(int s, int level, int optName, const void *optVal, int optLen)
{
    int rc = setsockopt(s, level, optName, optVal, optLen);
    if (rc < 0)
    {
        logError("SetSockOpt error");
    }
    return rc;
}

int Peanut::Bind(int sockFd, sockaddr *myAdd, int addLen)
{
    int rc = bind(sockFd, myAdd, addLen);
    if (rc < 0)
    {
        logError("Bind error");
    }
    return rc;
}

int Peanut::Listen(int s, int backlog)
{
    int rc =listen(s, backlog);
    if (rc < 0)
    {
        logError("Listen error");
    }
    return rc;
}


int Peanut::OpenListenFd(int port)
{
    int listenFd, optVal = 1;
    struct sockaddr_in serverAdd;

    /** Create a socket descriptor */
    if ((listenFd = Socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        return listenFd;
    }

    /** Eliminates "Address already in use" error from bind. */
    if (SetSockOpt(listenFd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optVal, sizeof(int)) < 0)
    {
        return -1;
    }

    /** ListenFd will be an endpoint for all requests to port
    on any IP address for this host */
    bzero((char *)&serverAdd, sizeof(serverAdd));
    serverAdd.sin_family = AF_INET;
    serverAdd.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAdd.sin_port = htons((unsigned short)port);
    if (Bind(listenFd, (sockaddr *)&serverAdd, sizeof(serverAdd)) < 0)
    {
        return -1;
    }

    /* Make it a listening socket ready to accept connection requests */
    if (Listen(listenFd, S2i(getValue(CFG_SERVER, CFG_SERVER_BACKLOG))) < 0)
    {
        return -1;
    }

    return listenFd;
}
