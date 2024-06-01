#ifndef __WD_FUNC_H
#define __WD_FUNC_H

#define _GNU_SOURCE

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
#include<sys/mman.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/select.h>
#include<sys/epoll.h>
#include<sys/ioctl.h>

#define SIZE(a) (sizeof(a)/sizeof(a[0]))

#define ARGS_CHECK(argc,num) {if(argc!=num) {printf("error args\n");return -1;}}

#define ERROR_CHECK(ret,retval,func_name) {if(ret==retval) {printf("error in %s line %d\n",__FILE__,__LINE__);fflush(stdout);perror(func_name);return -1;}}

#define THREAD_ERR_CHECK(ret,func_name) {if(ret!=0) {printf("%s failed,%d %s\n",func_name,ret,strerror(ret));return -1;}}

#define SELFFUNC_ERR_CHECK(ret,func_name) {if(ret!=0) {printf("%s failed\n",func_name);return -1;}}

typedef void (*sighandler_t)(int);

#endif











