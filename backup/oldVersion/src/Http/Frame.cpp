/*
* Author: micle 2018/01/25
* Env: debian 9, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#include "Frame.h"



/**
 * @Desc Deal with the connection;
 * */
void Handler(int client_fd)
{
    int maxSize = StrUtil::suS2i(Conf().getValue(CFG_SERVER, CFG_SERVER_REQSIZE));
    char buf[maxSize] = {0};
    int read_size = read(client_fd, buf, maxSize);

    if(read_size > 0)
    {
        Dispatcher dispatcher(buf);
        std::string send_buf_size = Conf().getValue(CFG_SERVER, CFG_SERVER_RESSIZE);
        unsigned char send_buf[StrUtil::suS2i(send_buf_size) + 1] = {0};
        int size = dispatcher.getRes(send_buf);
        if (send(client_fd, send_buf, size, 0) == -1) {
            Log::logError("Send response error!");
        }
        Log::logSuccess("Send OK\n");

        shutdown(client_fd, SHUT_RDWR);
        close(client_fd);
    } else
    {
        Log::logError("Reading: stream error!");
        // TODO 500
    }
}


void Frame::ProcessFrame(int sock)
{
    sockaddr_in remoteAdd;
    int client_fd;

    while (true) {
        unsigned int sin_size = sizeof(sockaddr_in);
        if ((client_fd = accept(sock, (sockaddr *) (&remoteAdd), &sin_size)) == -1)
        {
            Log::logError("Accept error!");
            continue;
        }
        Log::logInfo("Receive connection from: ");
        Log::logInfo(inet_ntoa(remoteAdd.sin_addr));

        // Father process do not wait for son process exit;
        signal(SIGCLD, SIG_IGN);

        pid_t pid;
        if ((pid = fork()) > 0)
        { // Father process;
            continue;
        }
        else if (pid == 0)
        { // Son process;
            Handler(client_fd);
            std::cout<<"子进程处理\n";
            exit(EXIT_SUCCESS);
        }
        else
        { // Fork failed;
            Log::logError("TCP:fork");
            exit(EXIT_FAILURE);
        }
    }
}


void setNonBlocking(int sock)
{
    int opts;
    opts = fcntl(sock, F_GETFL);
    if (opts < 0)
    {
        Log::logError("fcntl(sock, F_GETFL)");
        exit(1);
    }
    opts = opts | O_NONBLOCK;
    if (fcntl(sock, F_SETFL, opts) < 0)
    {
        Log::logError("fcntl(sock, F_SETFL, opts)");
        exit(1);
    }
}


int Frame::EpollThreadFrame(int sock)
{
    ThreadPool threadPool(20);

    struct epoll_event ev, events[20];
    int ePfd = epoll_create(256);

    // Set socket nonBlock;
    setNonBlocking(sock);

    // Set event
    ev.data.fd = sock;
    ev.events = EPOLLIN | EPOLLET;

    // Register epoll event;
    epoll_ctl(ePfd, EPOLL_CTL_ADD, sock, &ev);

    int curfds = 1;
    while ( true )
    {
        // Wait for epoll return events;
        int nfds = epoll_wait(ePfd, events, curfds, -1);

        // Deal events;
        for (int i = 0; i < nfds; ++i)
        {
            int client_fd;
            if (events[i].data.fd == sock) // New connection;
            {
                struct sockaddr_in clientAdd;
                socklen_t clilen;
                client_fd = accept(sock, (sockaddr *)&clientAdd, &clilen);
                if (client_fd < 0)
                {
                    perror("client_fd < 0");
                    continue;
                }
                char *str = inet_ntoa(clientAdd.sin_addr);
                std::cout << "Accept a connection from: " << str << std::endl;

                // Set read opt;
                setNonBlocking(client_fd);
                ev.data.fd = client_fd;
                ev.events = EPOLLIN | EPOLLET;
                if (epoll_ctl(ePfd, EPOLL_CTL_ADD, client_fd, &ev) < 0) {
                    Log::logError("Add socket to ePoll failed!");
                }
                curfds++;
            }
            else
            {
                threadPool.addTask([client_fd]{ Handler(client_fd);});
            }
        }
    }
}