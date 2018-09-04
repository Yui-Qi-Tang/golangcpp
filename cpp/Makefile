
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
BLD_NUM=build.number
INC = -Iinc
CFLAGS= -g -O0 -Wall -Wextra

CC=g++

SOURCES=$(wildcard $(SRC)/*.cpp)
# https://ftp.gnu.org/old-gnu/Manuals/make-3.79.1/html_chapter/make_10.html#SEC101
# https://www.quora.com/What-does-o-cpp-in-a-Makefile-mean
# https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html
#$(OBJ)/%.o: $(SRC)/%.cpp
#	$(CC)  -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

all: pre_check


pre_check:
	@if ! test -f $(OBJ); then mkdir -p $(OBJ); fi
	@if ! test -f $(DBJ); then mkdir -p $(DBJ); fi

build_test:
	$(CC) -c $(SOURCES)

build_o:
	$(OBJ)/%.o: $(SRC)/%.cpp
		$(CC) $(INC) -c $< -o $@