# 对当前目录每个文件生成一个对应的可执行程序
SRCS_C  :=$(wildcard *.c)
SRCS_CC :=$(wildcard *.cc)
SRCS_CPP:=$(wildcard *.cpp)

TARGETS_C:=$(SRCS_C:%.c=%)
TARGETS_CC:=$(SRCS_CC:%.cc=%)
TARGETS_CPP:=$(SRCS_CPP:%.cpp=%)

TARGETS:=$(TARGETS_C) $(TARGETS_CC) $(TARGETS_CPP)

CC := gcc
CXX := g++
CFLAGS := -Wall -g
CXXFLAGS := -Wall -g -std=c++11

all : $(TARGETS)

% : %.c
	$(CC) $(CFLAGS) $< -o $@

% : %.cc
	$(CXX) $(CXXFLAGS) $< -o $@

% : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean rebuild

clean:
	rm -rf $(TARGETS)

rebuild: clean all