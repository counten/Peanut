#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory.h>

#define MAXLINE 500
#define LISTENQ 20
#define SERV_PORT 8081

void setNonBlocking(int sock)
{
    int opts;
    opts = fcntl(sock, F_GETFL);
    if (opts < 0)
    {
        perror("fcntl(sock,GETFL)");
        exit(1);
    }
    opts = opts | O_NONBLOCK;
    if (fcntl(sock, F_SETFL, opts) < 0)
    {
        perror("fcntl(sock,SETFL,opts)");
        exit(1);
    }
}

int main()
{
    int i,
            listenfd,
            confd,
            sockfd,
            epfd,
            nfds,
            port = SERV_PORT;
    ssize_t n;
    char line[MAXLINE];
    socklen_t clilen;

    /* 声明epoll_event结构体的变量,ev用于注册事件,数组用于回传要处理的事件 */
    struct epoll_event ev, events[20];

    /*生成用于处理accept的epoll专用的文件描述符 */
    epfd = epoll_create(256);
    struct sockaddr_in clientAdd;
    struct sockaddr_in serverAdd;

    // Create socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    // Set socket nonBlock;
    setNonBlocking(listenfd);

    // Set event
    ev.data.fd = listenfd;
    ev.events = EPOLLIN | EPOLLET;

    // Register epoll event;
    epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);

    char localAdd[] = "127.0.0.1";
    bzero(&serverAdd, sizeof(serverAdd));
    serverAdd.sin_family = AF_INET;
    inet_aton(localAdd, &(serverAdd.sin_addr));
    serverAdd.sin_port = htons(port);

    // Bind
    bind(listenfd, (sockaddr *)&serverAdd, sizeof(serverAdd));

    // Listen
    listen(listenfd, LISTENQ);
    while ( true )
    {
        // Wait for epoll return events;
        nfds = epoll_wait(epfd, events, 20, 500);

        // Deal events;
        for (i = 0; i < nfds; ++i)
        {
            if (events[i].data.fd == listenfd) // New connection;
            {
                confd = accept(listenfd, (sockaddr *)&clientAdd, &clilen);
                if (confd < 0)
                {
                    perror("connfd<0");
                    exit(1);
                }
                char *str = inet_ntoa(clientAdd.sin_addr);
                std::cout << "Accept a connection from: " << str << std::endl;

                // Set read opt;
                ev.data.fd = confd;
                ev.events = EPOLLIN | EPOLLET;
                epoll_ctl(epfd, EPOLL_CTL_ADD, confd, &ev);
            }
            else if (events[i].events & EPOLLIN) // Connected, read;
            {
                if ((sockfd = events[i].data.fd) < 0)
                {
                    continue;
                }

                if ((n = read(sockfd, line, MAXLINE)) < 0)
                {
                    if (errno == ECONNRESET)
                    {
                        close(sockfd);
                        events[i].data.fd = -1;
                    }
                    else
                    {
                        std::cout << "readLine error" << std::endl;
                    }
                }
                else if (n == 0)
                {
                    close(sockfd);
                    events[i].data.fd = -1;
                }

                std::cout << "Read: " << line << std::endl;

                // Set write opt;
                ev.data.fd = sockfd;
                ev.events = EPOLLOUT | EPOLLET;
                epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);
            }
            else if (events[i].events & EPOLLOUT) // Send data;
            {
                sockfd = events[i].data.fd;
                std::string response = "Content-Length: 8\n"
                        "Content-Type: text/html;charset=UTF-8\n"
                        "Date: Wed, 24 Jan 18 02:50:41 GMT\n"
                        "Server: mnServer(0.1 alpha)/Linux @http://codeyourlife.cn/ \n"
                        "Content: 12345678";
                int len = response.size();
                write(sockfd, response.c_str(), len);
                std::cout << "Send Ok !";

                // Set read opt;
                ev.data.fd = sockfd;
                ev.events = EPOLLIN | EPOLLET;
                epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
            }
        }
    }
}