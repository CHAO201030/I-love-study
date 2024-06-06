#ifndef __H_NET_H__
#define __H_NET_H__

#include "H_head.h"

#define ROUTE_IP "192.168.7.121"
#define ROUTE_PORT "9527"

#define CLUSTER_1_IP "192.168.7.121"
#define CLUSTER_1_PORT "9528"

#define CLUSTER_2_IP "192.168.7.121"
#define CLUSTER_2_PORT "9529"

int tcp_init(const char* ip, const char* port);

int tcp_accept(int sfd);

void epoll_add(int epfd, int fd);

void epoll_del(int epfd, int fd);

#endif