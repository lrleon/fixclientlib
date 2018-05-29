
# you could perfectly change the compiler to gcc or icc. But if you
# disallow clang, then be sure of comment CCLINK
CXX = clang++
CC = clang

# you can also change this programs to the more tradionals ones
AR = llvm-ar clq
RANLIB = llvm-ranlib
LD = llvm-link

# you can comment this, but you would loose clang sanitizer features
CCLINK = clang++ -fsanitize=address,undefined

# Be sure that ASIO enviroment var exists and points to cloned asio
# repository on the branch cpp11-only
ASIO = $(shell echo $$ASIO)

INCLUDE = -I. -I../include -I$(ASIO)/asio/include

FIXCLIENTLIBPATH = ../src/

FLAGS=-DDEBUG -O0 -g3 -D_REENTRANT -fsanitize=address,undefined

DEFINES= -D_GLIBCXX__PTHREADS

WARN= -Wall -Wextra -Wcast-align -Wno-sign-compare -Wno-write-strings -Wno-parentheses

OPTIONS= $(FLAGS) $(WARN) $(DEFINES)

CXXFLAGS= -std=c++14 $(INCLUDE) $(OPTIONS)

SRCS = test-fix-session.cc

OBJS = $(SRCS:.cc=.o)

test-fix-session: test-fix-session.cc $(FIXCLIENTLIBPATH)/libfmfixclient.a
	$(CXX) $(FLAGS) $(INCLUDE) $@.cc -o $@ -L$(FIXCLIENTLIBPATH) -lfmfixclient

all: test-fix-session

clean:
	$(RM) $(OBJS) test-fix-session

depend:
	makedepend -- $(FLAGS) $(INCLUDE) -- $(SRCS)
