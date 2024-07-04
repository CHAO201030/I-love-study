SRCS_CC:=$(wildcard *.cc)
SRCS_CPP:=$(wildcard *.cpp)
SRCS:=$(SRCS_CC)$(SRCS_CPP)

TARGET:=main

CXX:=g++
CXXFLAGS:=-Wall -g -std=c++11

all:$(TARGET)

$(TARGET):$(SRCS)
	$(CXX) $^ -o $@ $(CXXFLAGS)

clean:
	rm -rf $(TARGET)

rebuild: clean $(TARGET)
