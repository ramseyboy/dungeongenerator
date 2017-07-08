CFLAGS=-std=c99 -Wall
DFLAGS=-betterC
BIN=bin
ARTIFACT=dungen
OUT=$(BIN)/out

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

INCLUDE=-Iinclude
LIB= -L. -ltcod -ltcodxx -L/Library/D/dmd/lib/ -lphobos2 -pthread
C_SRC=src/*.c
D_SRC=src/*.d


all:
	mkdir -p $(OUT)
	dmd $(DFLAGS) -c -od=$(OUT) $(D_SRC)
	clang $(CFLAGS) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(INCLUDE) $(LIB) $(C_SRC) $(OUT)/random.o -o $(BIN)/$(ARTIFACT)

run:
	./$(BIN)/$(ARTIFACT)

clean:
	rm -r $(BIN)
	
