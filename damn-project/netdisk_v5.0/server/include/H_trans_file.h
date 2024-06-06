#ifndef __H_TRANS_FILE_H__
#define __H_TRANS_FILE_H__

#include "H_head.h"

#define BUFFER_SIZE 1024
#define BIG_FILE_SIZE ((off_t)(1<<20) * 100)
#define MMAP_SIZE 4096
#define FILE_NAME "file1.txt"

typedef struct{
    int data_len;
    char data_buf[BUFFER_SIZE];
}train_t;

off_t get_file_size(int fd);

void send_file(int sfd);

void recv_file(int sfd);

void send_cluster_info(int sfd, const char *ip, const char *port);

void sendn(int sfd, void *buf, int buf_len);

void recvn(int sfd, void *buf, int buf_len);

#endif