
CXX = clang++
CC = clang

INCLUDE = -I. -I ../include

FLAGS=-DDEBUG -O0 -g3 -D_REENTRANT -D__extern_always_inline="extern __always_inline"

DEFINES= -D_GLIBCXX__PTHREADS

WARN= -Wall -Wextra -Wcast-align -Wno-sign-compare -Wno-write-strings -Wno-parentheses

OPTIONS= $(FLAGS) $(WARN) $(DEFINES)

CXXFLAGS= -std=c++14 $(INCLUDE) $(OPTIONS)

SRCS = FixSession.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(OBJS)
