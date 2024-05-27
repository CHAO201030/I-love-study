#目前是最通用的Makefile
out:=main
SRCS:=$(wildcard *.c) #拿到当前目录下所有的c文件
OBJS:=$(patsubst %.c,%.o,$(SRCS))
#预定义变量 -I../include
CC:=gcc
CFLAGS:=-g -D DEBUG 
$(out):$(OBJS)
	gcc $^ -o $@ -pthread #-I /usr/include/mysql/ -lmysqlclient
.PHONY:clean rebuild
rebuild:clean $(out)
clean:
	rm -rf $(OBJS) $(out)
