#include <func.h>

#define SERV_IP "192.168.239.128"
#define SERV_PORT "9527"
#define BACKLOG 10
#define BUFFER_SIZE 256
#define MAX_CAPACITY 10
#define TIME_OUT 30

typedef struct{
    int connect_flag;
    time_t connect_time;
}user_t;

// API
int tcp_init(char *ip, char *port);
int epoll_add(int epfd, int fd);
int epoll_del(int epfd, int fd);
int set_nonblock(int fd);

int main(int argc, char* argv[])
{
    int socket_fd = tcp_init(SERV_IP, SERV_PORT);
    ERROR_CHECK(socket_fd, -1, "tcp_init");

    int epfd = epoll_create(1);
    ERROR_CHECK(epfd, -1, "epoll_create");
    printf("%d\n",epfd);

    int ret = epoll_add(epfd, socket_fd);
    ERROR_CHECK(ret, -1, "epoll_add");

    struct epoll_event evs[MAX_CAPACITY];

    int ready_fd_num = 0;

    char trans_buf[2 * BUFFER_SIZE] = {0};
    char recv_buf[BUFFER_SIZE] = {0};

    user_t user_table[MAX_CAPACITY] = {0};
    time_t end_time = time(NULL);
    
    while(1)
    {
        ready_fd_num = epoll_wait(epfd, evs, MAX_CAPACITY, 1000);
        end_time = time(NULL);

        for(int i = 0; i < ready_fd_num; i++)
        {
            if(evs[i].data.fd == socket_fd)
            {
                // 接收新客户端连接请求
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                bzero(&client_addr, sizeof(client_addr));

                int client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &client_len);
                if(client_fd == -1)
                {
                    continue;
                }

                ret = set_nonblock(client_fd);
                if(ret == -1)
                {
                    printf("INFO : SET_NONBLOCK failed\n");
                    continue;
                }

                ret = epoll_add(epfd, client_fd);
                if(ret == -1)
                {
                    printf("INFO : EPOLL_ADD failed\n");
                    continue;
                }

                user_table[client_fd - 5].connect_flag = 1;  // stdin stdout stderr sfd epfd client_fd....
                user_table[client_fd - 5].connect_time = time(NULL);
                printf("INFO : Client %s connected\n", inet_ntoa(client_addr.sin_addr));
            }
            else
            {
                if(evs[i].events & EPOLLIN)
                {
                    int user_id = evs[i].data.fd - 5;
                    int n = recv(evs[i].data.fd, recv_buf, BUFFER_SIZE, 0);
                    if(n > 0)
                    {
                        // 对数据转发
                        user_table[user_id].connect_time = time(NULL);
                        recv_buf[n] = '\0';
                        
                        sprintf(trans_buf, "User_%d : %s", user_id + 1, recv_buf);

                        for(int j = 0; j < MAX_CAPACITY; j++)
                        {
                            if(user_table[j].connect_flag > 0 && j != user_id)
                            {
                                send(j + 5, trans_buf, strlen(trans_buf), 0);
                            }
                        }
                    }
                    else if(n == 0)
                    {
                        // 对端断开连接 取消监听
                        printf("INFO : Client %d leave\n", user_id + 1);
                        user_table[evs[i].data.fd - 5].connect_flag = 0;
                        epoll_del(epfd, evs[i].data.fd);
                        close(evs[i].data.fd);
                        continue;
                    }
                    else
                    {
                        // 发生错误
                        printf("INFO : Recv Client %d msg failed\n", user_id);
                        continue;
                    }
                }
            }
        }
        
        // 超时断开机制
        for(int i = 0; i < MAX_CAPACITY; i++)
        {
            if(user_table[i].connect_flag > 0 && end_time - user_table[i].connect_time >= TIME_OUT)
            {
                printf("INFO : Client %d leave\n", i + 1);
                user_table[i].connect_flag = 0;
                epoll_del(epfd, i + 5);
                close(i + 5);
                continue;
            }
        }
    }

    return 0;
}

int tcp_init(char *ip, char *port)
{
    struct sockaddr_in ser_addr;
    bzero(&ser_addr, sizeof(ser_addr));
    
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr(ip);
    ser_addr.sin_port = htons(atoi(port));

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(socket_fd, -1, "socket");

    int reuse = 1;
    int ret = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
    ERROR_CHECK(ret, -1, "setsockopt");

    ret = bind(socket_fd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
    ERROR_CHECK(ret, -1, "bind");

    ret = listen(socket_fd, BACKLOG);
    ERROR_CHECK(ret, -1, "listen");

    return socket_fd;
}

int epoll_add(int epfd, int fd)
{
    struct epoll_event event;
    bzero(&event, sizeof(event));
    event.events = EPOLLIN;
    event.data.fd = fd;

    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
    ERROR_CHECK(ret, -1, "epoll_ctl_add");

    return 0;
}

int epoll_del(int epfd, int fd)
{
    struct epoll_event event;
    bzero(&event, sizeof(event));
    event.events = EPOLLIN;
    event.data.fd = fd;

    int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &event);
    ERROR_CHECK(ret, -1, "epoll_ctl_del");

    return 0;
}

int set_nonblock(int fd)
{
    // 设置非阻塞I/O
    int status = fcntl(fd, F_GETFL);
    status |= O_NONBLOCK;
    int ret = fcntl(fd, F_SETFL, status);
    ERROR_CHECK(ret, -1, "fcntl");

    return 0;
}