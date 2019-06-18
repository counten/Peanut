/*
* Author: wbq813 2018/3/13
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn 
*/
#include "Peanut.h"

#include <sys/socket.h>
#include <sys/epoll.h>
#include <functional>
#include <signal.h>
#include <arpa/inet.h>

// Inner Project
#include "../Log/Log.h"
#include "../Http/Tcp.h"
#include "EPollUtil.h"
#include "ThreadPool.h"
#include "../Http/HttpHandle.h"
#include "../Conf/Conf.h"
#include "../Util/StrUtil.h"

/** Block some signal*/
void blockSig(int sigNo) {
    sigset_t signal_mask;
    sigemptyset(&signal_mask);
    sigaddset(&signal_mask, sigNo);
    int rc = pthread_sigmask(SIG_BLOCK, &signal_mask, NULL);
    if (rc != 0) {
        logError("blockSig error");
    }
}

/**
 * @Desc Use EPoll and thread poll to solve request;
 * */
void Peanut::SchemeEPollThreadPool() {
    int listenFd = OpenListenFd(S2i(getValue(CFG_SERVER, CFG_SERVER_PORT)));
    logInfo("ServerInit: Listen to port!");

    // multi process.
//    for(int i =1; i<4; i++)
//    {
//        pid_t pid =  fork();
//        if(pid ==0)
//        {
//            break;
//        } else if(pid < 0)
//        {
//            logError("fork error");
//            continue;
//        }
//    }


    epoll_event events[MAX_EVENT_NUM];
    // client information.
    sockaddr clnAdd;
    socklen_t clnLen = sizeof(clnAdd);

    blockSig(SIGPIPE);

    int ePollFd = EPollCreate(1024);
    addFd(ePollFd, listenFd, false);
    ThreadPool pools(8, 1600);
    HttpHandle::setEPollFd(ePollFd);
    HttpHandle handle[1600];
    logInfo("ServerInit: Create thread pool!");
    logSuccess("ServerInit: OK!");

    logInfo("Run process:", getpid());
    while(true)
    {
        int eventNum = EPollWait(ePollFd, events, MAX_EVENT_NUM, -1);
        for (int i = 0; i < eventNum; ++i)
        {
            int sockFd = events[i].data.fd;
            if (sockFd == listenFd) { /** receive connection */
                while(true)
                {
                    /**The returned socket descriptor connect with client;
                     * listenFd do not associate with client, and keep be used to receive other connection.
                     */
                    int connFd = accept(listenFd, &clnAdd, &clnLen);
                    if (connFd == -1) {
                        if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
                        {
                            /** Connection finished*/
                            break;
                        }
                        else
                            {
                            logError("accept error");
                        }
                    }
                    sockaddr_in sin;
                    memcpy(&sin, &clnAdd, sizeof(sin));
                    handle[connFd].init(connFd, inet_ntoa(sin.sin_addr)); /** Init */
                    addFd(ePollFd, connFd, true); /** Add to listen*/
                }
            }
            else
            { /** There are data to read or write*/
            // 绑定指向成员函数的指针,
                pools.addTask(std::bind(&HttpHandle::process, &handle[sockFd]));
            }
        }
    }
}
