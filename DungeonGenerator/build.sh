#!/usr/bin/env bash

clang++ -std=c++11 -stdlib=libc++ -o out/gen -Iinclude -L. -ltcod -ltcodxx -Wall `sdl2-config --cflags --libs` src/*.cpp
