# 多对一
Srcs := $(wildcard *.c)
Objs := $(patsubst %.c, %.o, $(Srcs))
Out  := cluster_1

CC := gcc
CFLAGS = -Wall -g -lpthread

$(Out) : $(Objs)
	$(CC) $^ -o $@ $(CFLAGS)
%.o: %.c algs.h
	$(CC) -c $< $(CFLAGS)

.PHONY: clean rebuild print
clean:
	$(RM) $(Objs) $(Out)
rebuild: clean $(Out)

print:
	echo $(patsubst %.c, %.o, foo.c.c bar.c)
