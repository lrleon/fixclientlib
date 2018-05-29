
# you could perfectly change the compiler to gcc or icc
CXX = clang++
CC = clang

# you can also change this programs to the more tradionals ones
AR = llvm-ar clq
RANLIB = llvm-ranlib
LD = llvm-link

# Be sure that ASIO enviroment var exists and points to cloned asio
# repository on the branch cpp11-only
ASIO = $(shell echo $$ASIO)

INCLUDE = -I. -I../include -I$(ASIO)/asio/include

FLAGS=-DDEBUG -O0 -g3 -D_REENTRANT -D__extern_always_inline="extern __always_inline"

DEFINES= -D_GLIBCXX__PTHREADS

WARN= -Wall -Wextra -Wcast-align -Wno-sign-compare -Wno-write-strings -Wno-parentheses

OPTIONS= $(FLAGS) $(WARN) $(DEFINES)

CXXFLAGS= -std=c++14 $(INCLUDE) $(OPTIONS)

SRCS = FixSession.cc init.cc

OBJS = $(SRCS:.cc=.o)

libfmfixclient.a: $(OBJS)
	$(RM) $@
	$(AR) $@ $(OBJS)
	$(RANLIB) $@

all: libfmfixclient.a

clean:
	$(RM) $(OBJS) libfmfixclient.a
