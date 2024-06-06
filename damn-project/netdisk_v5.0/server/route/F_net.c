#include "../include/H_net.h"

#define BACKLOG 10

int tcp_init(const char* ip, const char* port)
{
    int sfd = -1;
    if((sfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        error(-1, errno, "socket failed\n");
    }

    int reuse = 1;
    if(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
    {
        error(-1, errno, "setsockopt failed\n");
    }

    struct sockaddr_in ser_addr;
    bzero(&ser_addr, sizeof(ser_addr));

    socklen_t ser_len = sizeof(ser_addr);

    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr(ip);
    ser_addr.sin_port = htons(atoi(port));

    if(bind(sfd, (struct sockaddr *)&ser_addr, ser_len) == -1)
    {
        error(-1, errno, "bind failed\n");
    }

    if(listen(sfd, BACKLOG) == -1)
    {
        error(-1, errno, "listen failed\n");
    }

    return sfd;
}

int tcp_accept(int sfd)
{
    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));

    socklen_t client_len = sizeof(client_addr);

    int client_fd = -1;
    if((client_fd = accept(sfd, (struct sockaddr *)&client_addr, &client_len)) == -1)
    {
        printf("INFO : accept failed\n");
        return -1;
    }
    
    int status = fcntl(client_fd, F_GETFL);
    status |= O_NONBLOCK;
    if(fcntl(client_fd, F_SETFL, status) == -1)
    {
        printf("INFO : set no block client_fd failed\n");
        return -1;   
    }

    printf("INFO : %s %d connected...\n", 
            inet_ntoa(client_addr.sin_addr), 
            ntohs(client_addr.sin_port));
            
    return client_fd;
}

void epoll_add(int epfd, int fd)
{
    struct epoll_event event;
    bzero(&event, sizeof(event));

    event.events = EPOLLIN;
    event.data.fd = fd;

    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
}

void epoll_del(int epfd, int fd)
{
    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
}
