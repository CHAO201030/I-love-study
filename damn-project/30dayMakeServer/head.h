#ifndef __HEAD_H__
#define __HEAD_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<errno.h>
#include<error.h>
#include<time.h>
#include<unistd.h>
#include<signal.h>
#include<dirent.h>
#include<assert.h>
#include<fcntl.h>
#include<pthread.h>
#include<ctype.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<sys/mman.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/select.h>
#include<sys/epoll.h>
#include<sys/ioctl.h>

#define ARGS_CHECK(argc, num) do{if(argc!=num){printf("Error args\n");return -1;}}while(0)

#define ERROR_CHECK(ret, retval, func_name) do{if(ret==retval){printf("Error in %s -> %d\n", __FILE__,__LINE__);fflush(stdout);perror(func_name);return -1;}}while(0)

#define THREAD_ERR_CHECK(ret, func_name) do{if(ret!=0){printf("%s failed, %d %s\n", func_name, ret, strerror(ret));return -1;}}while(0)

#define SELF_FUNC_ERR_CHECK(ret, func_name) do{if(ret!=0){printf("%s failed\n", func_name);return -1;}}while(0)

typedef void (*sighandler_t)(int);

#endif











