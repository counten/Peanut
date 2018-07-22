/*
* Author: micle 2017/12/12
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/


#include "Tcp.h"


int Tcp::createSocket()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        Log::logError("Socket create fail!");
    }
    return sock;
}

int Tcp::Bind(int sock)
{
    //reuse port on server
    int opt = SO_REUSEADDR;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        Log::logError("Bind: setSockOpt");
        return -1;
    }

    sockaddr_in myAdd;
    bzero(&myAdd, sizeof(struct sockaddr_in));

    myAdd.sin_family = AF_INET;
    myAdd.sin_port = htons(StrUtil::suS2i(Conf().getValue(CFG_SERVER, CFG_SERVER_PORT)));
    myAdd.sin_addr.s_addr = INADDR_ANY;
    bzero(&(myAdd.sin_zero), 8);
    if (bind(sock, (sockaddr *) (&myAdd), sizeof(sockaddr)) == -1)
    {
        Log::logError("Bind error! sock ");
        return 1;
    }
    return 0;
}

int Tcp::Listen(int sock)
{
    if (listen(sock, StrUtil::suS2i(Conf().getValue(CFG_SERVER, CFG_SERVER_BACKLOG))) == -1)
    {
        Log::logError("Listen error");
        return 1;
    }

    // Use different frame!
//    Frame::EpollThreadFrame(sock);
    Frame::ProcessFrame(sock);
}




