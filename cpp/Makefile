# versioning
MAJOR=0
MINOR=1
PATCH=0
VERSION=$(MAJOR).$(MINOR).$(PATCH)

BIN=$(notdir $(CURDIR))
DBG=$(BIN)g

SRC=src
INC=inc
OBJ=obj/bin
DBJ=obj/dbg
BLD=bin

CXX=g++

# SOURCES=$(wildcard $(SRC)/*.cpp)
# https://ftp.gnu.org/old-gnu/Manuals/make-3.79.1/html_chapter/make_10.html#SEC101
# https://www.quora.com/What-does-o-cpp-in-a-Makefile-mean
# https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html

# 這裡下make沒反應
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX)  -c $< -o $@

all: pre_check

pre_check:
	@if ! test -f $(OBJ); then mkdir -p $(OBJ); fi
	@if ! test -f $(DBJ); then mkdir -p $(DBJ); fi
