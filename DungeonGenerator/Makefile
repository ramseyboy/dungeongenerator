CXX=clang++
CXXFLAGS=-std=c++11 -stdlib=libc++ -Wall
BIN=bin

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

INCLUDE=-Iinclude
LIB=-ltcod -ltcodxx
SRC=src/main.cpp

all:
	mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $(SDL_CFLAGS) $(SDL_LDFLAGS) -o $(BIN)/gen $(INCLUDE) -L. $(LIB) $(SRC)

run:
	./$(BIN)/gen

clean:
	rm -r $(BIN)
	
