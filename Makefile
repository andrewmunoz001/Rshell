CC = g++
CC_FLAGS = -Wall -Werror -ansi -pedantic
SRC = ./src/
BIN = ./bin/
EXEC = $(BIN)rshell
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES: .cpp = .o)

all:
	[ ! -d ./bin  ] && mkdir -p ./bin
	$(CC) $(CC_FLAGS) $(SRC)shell.cpp $(SRC)cmdComposite.cpp $(SRC)Parse.cpp -o $(EXEC) 

rshell:
	all
clean:
	rm -rf $(BIN) 
