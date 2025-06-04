# Common Makefile definitions

RM=rm -f

# If running from cmake, the command sets SWIPL=${PROG_SWIPL}
#       - See also: current_prolog_flag(executable, Exe)
ifdef SWIPL
BUILD_BIN_DIR?=$(dir $(SWIPL))
else
BUILD_BIN_DIR?=$(dir $(shell which swipl))
SWIPL?=$(BUILD_BIN_DIR)swipl
endif
PATH_WITH_SWIPL?=$(realpath -s $BUILD_BIN_DIR):$$PATH

# Where to find descriptor.proto:
PROTOC_DOTDOT:=$(realpath -s $(dir $(shell which protoc))/..)
PROTOC_INCLUDE=$(PROTOC_DOTDOT)/include
PROTOC_LIB:=$(PROTOC_DOTDOT)/lib

PROTOC_GEN_PROLOG_PB=gen_pb

# If SHELL is bash, can use `type -p protoc` instead of `which protoc`
# Requires having done "make" in ~/src/protobufs:
#   PROTOC:=$(realpath -s $(HOME)/src/protobuf/src/protoc)
PROTOC:=$(shell which protoc)
# Requires having LD_LIBRARY_PATH=$(realpath ../../../../protobuf/src/.libs):
#   PROTOC:=$(realpath -s $(HOME)/src/protobuf/src/.libs/protoc)

# If using $SRC/protobuf from git@github.com:protocolbuffers/protobuf.git:
#   -I$(SRC)/protobuf/src/google/protobuf
PROTOC_I=-I. -I../demo -I../interop -I$(PROTOC_INCLUDE)

# This is essentially what GNU Make 4.2.1 uses as a built-in rule:
#   CXX=g++
#   %o: %.cpp
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

# Don't specify -Wall -- it produces warnings from the generated *.pb.cc files
CFLAGS=-O0
CXXFLAGS=-O0
# flags from pkg-config: -pthread -lprotobuf -lpthread
CPPFLAGS:=$(shell pkg-config --cflags protobuf)
LDFLAGS:=$(shell pkg-config --libs protobuf)

PYTHON:=$(shell which python3)
