#pragma once

#include "libtcod.hpp"
#include "tile.h"
#include "random.h"

class Map : public ITCODBspCallback {
 public:
  int width, height;

  Map(int width, int height);
  ~Map();
  bool isWall(int x, int y) const;
  void render() const;
  bool visitNode(TCODBsp *node, void *userData);

 private:
  static const int ROOM_MAX_SIZE = 12;
  static const int ROOM_MIN_SIZE = 6;

  Tile *tiles;

  int roomNum = 0;   // room number
  int lastx, lasty;  // center of the last room

  Random *rand;

  void dig(int x1, int y1, int x2, int y2);
  void createRoom(bool first, int x1, int y1, int x2, int y2);

  void setWall(int x, int y);
};