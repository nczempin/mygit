CC=g++
#CC=g++
CFLAGS=-O2 -g -std=c++11 -pthread -Wall -Wextra -pedantic

BIN= mygit
SRC=$(wildcard **/*.cpp)
GAS=$(wildcard *.s)
NASM=$(wildcard *.asm)
CPP_OBJ=$(SRC:.cpp=.o)

OBJ=$(CPP_OBJ)

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $(BIN) $(CFLAGS)  $^ -lssl -lcrypto -lz
%.o: %.cpp
	$(CC) -o $@ -c $(CFLAGS) $^

.PHONY : clean
clean :
	-rm -f $(BIN) $(OBJ)
