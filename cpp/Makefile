# versioning
MAJOR=0
MINOR=1
PATCH=0
VERSION=$(MAJOR).$(MINOR).$(PATCH)

BIN=$(notdir $(CURDIR))
DBG=$(BIN)g

SRC=src
INC=inc
OBJ=obj/bin
DBJ=obj/dbg
BLD=bin
LIB=lib


CXX=g++
CXXFLAGS= -std=c++11 -lpthread -pthread


SOURCES=$(wildcard $(SRC)/*.cpp)
OBJS=$(notdir $(patsubst %cpp,%o,$(SOURCES)))
BIN_OBJS=$(addprefix $(OBJ)/,$(OBJS))
# https://ftp.gnu.org/old-gnu/Manuals/make-3.79.1/html_chapter/make_10.html#SEC101
# https://www.quora.com/What-does-o-cpp-in-a-Makefile-mean
# https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html
# make會按照rule patten執行命令


$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS)  -c $< -o $@

.PHONY: clean

all: pre_check $(BIN_OBJS) $(BLD)/$(BIN)

$(BLD)/$(BIN): $(BIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $(BLD)/$(BIN) $(BIN_OBJS)

pre_check:
	@if ! test -f $(OBJ); then mkdir -p $(OBJ); fi
	@if ! test -f $(DBJ); then mkdir -p $(DBJ); fi
	@if ! test -f $(BLD); then mkdir -p $(BLD); fi

clean:
	rm -f $(BIN_OBJS) $(BLD)/* core
