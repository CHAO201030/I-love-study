#include "H_net.h"

int tcp_connect(const char *ip, const char *port)
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd == -1)
    {
        error(-1, errno, "socket failed\n");
    }

    struct sockaddr_in ser_addr;
    bzero(&ser_addr, sizeof(ser_addr));

    socklen_t ser_len = sizeof(ser_addr);

    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr(ip);
    ser_addr.sin_port = htons(atoi(port));

    if(connect(sfd, (struct sockaddr *)&ser_addr, ser_len) == -1)
    {
        error(-1, errno, "connect failed\n");
    }

    return sfd;
}

void epoll_add(int epfd, int fd)
{
    struct epoll_event event;
    bzero(&event, sizeof(event));

    event.events  = EPOLLIN;
    event.data.fd = fd;
    
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
}

void epoll_del(int epfd, int fd)
{
    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
}
