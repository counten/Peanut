#include "EPollUtil.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <cstring>
#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <sys/mman.h>
#include <cstdarg>
#include <cerrno>

// Inner project
#include "../Log/Log.h"

int setNonBlocking(int fd) /* 将文件描述符设置为非阻塞 */
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

void Peanut::addFd(int ePollFd, int fd, bool one_shot)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET; /* ET触发 */
    if (one_shot)
    {
        event.events |= EPOLLONESHOT; /* 这里特别要注意一下 */
    }
    epoll_ctl(ePollFd, EPOLL_CTL_ADD, fd, &event);
    setNonBlocking(fd);
}

void Peanut::removeFd(int epollFd, int fd)
{
    epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, 0);
    close(fd);
}

void Peanut::modFd(int ePollFd, int fd, int ev, bool oneShot)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = ev | EPOLLET; /* ET触发 */
    if (oneShot)
    {
        event.events |= EPOLLONESHOT;
    }
    epoll_ctl(ePollFd, EPOLL_CTL_MOD, fd, &event);
}

int Peanut::EPollCreate(int size)
{
    int rc = epoll_create(size);
    if (rc < 0)
    {
        logError("EPollCreate failed");
    }
    return rc; /* 否则的话,返回文件描述符 */
}

int Peanut::EPollWait(int ePfd, epoll_event *events, int maxEvents, int timeout)
{
    int rc;
    if ((rc = epoll_wait(ePfd, events, maxEvents, timeout)) == -1)
    {
        logError("EPoll failed");
    }
    return rc;
}
