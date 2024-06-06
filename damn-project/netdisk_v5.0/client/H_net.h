#ifndef __H_NET_H__
#define __H_NET_H__

#include "H_head.h"

int tcp_connect(const char *ip, const char *port);

void epoll_add(int epfd, int fd);

void epoll_del(int epfd, int fd);

#endif