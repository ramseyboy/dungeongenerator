C=clang
CFLAGS=-std=c99 -Wall
BIN=bin

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

INCLUDE=-Iinclude
LIB=-ltcod -ltcodxx
SRC=src/*.c

all:
	mkdir -p $(BIN)
	$(C) $(CFLAGS) $(SDL_CFLAGS) $(SDL_LDFLAGS) -o $(BIN)/gen $(INCLUDE) -L. $(LIB) $(SRC)

run:
	./$(BIN)/gen

clean:
	rm -r $(BIN)
	
