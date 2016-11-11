#pragma once

#include "libtcod.hpp"
#include "tile.h"

class Map {
 public:
  int width, height;

  Map(int width, int height);
  ~Map();
  bool isWall(int x, int y) const;
  void render() const;

 private:
  Tile *tiles;

  void setWall(int x, int y);
};