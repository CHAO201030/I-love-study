#include <func.h>

#define SERV_IP "192.168.239.128"
#define SERV_PORT "9527"
#define BUFFER_SIZE 256

int main(int argc, char* argv[])
{
    struct sockaddr_in ser_addr;
    bzero(&ser_addr, sizeof(ser_addr));
    
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr(SERV_IP);
    ser_addr.sin_port = htons(atoi(SERV_PORT));

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(socket_fd, -1, "socket");

    int ret = connect(socket_fd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
    ERROR_CHECK(ret, -1, "connect");

    int epfd = epoll_create1(0);
    ERROR_CHECK(epfd, -1, "epoll_create1");

    struct epoll_event event, evs[2];   // 2 for STDIN and socket_fd
    bzero(&event, sizeof(event));

    event.events = EPOLLIN;
    event.data.fd = socket_fd;

    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, socket_fd, &event);
    ERROR_CHECK(ret, -1, "epoll_ctl_add_sfd");

    event.data.fd = STDIN_FILENO;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    ERROR_CHECK(ret, -1, "epoll_ctl_add_stdin");

    int ready_fd_num = 0;
    char buf[BUFFER_SIZE] = {0};
    
    while(1)
    {
        ready_fd_num = epoll_wait(epfd, evs, 2, -1);
        
        for (int i = 0; i < ready_fd_num; i++)
        {
            if(evs[i].data.fd == STDIN_FILENO)
            {
                int n = read(STDIN_FILENO, buf, BUFFER_SIZE);
                if(n > 0)
                {
                    buf[n] = '\0';
                    ret = send(socket_fd, buf, n, 0);
                    ERROR_CHECK(ret, -1, "send");
                }
            }
            else if(evs[i].data.fd == socket_fd)
            {
                int n = recv(socket_fd, buf, BUFFER_SIZE, 0);
                if(n > 0)
                {
                    printf("%s", buf);
                    continue;
                }
                else if(n == 0)
                {
                    printf("Server shutdown\n");
                    return 0;
                }
            }
        }
    }

    return 0;
}