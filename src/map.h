#pragma once

#include "libtcod.h"
#include "tile.h"

class Map {
 public:
  static const int ROOM_MAX_SIZE = 12;
  static const int ROOM_MIN_SIZE = 6;

  int width, height;

  Map(int width, int height);
  ~Map();
  bool isWall(int x, int y) const;

  bool isInFov(int x, int y) const;
  bool isExplored(int x, int y) const;
  void computeFov();

  void render() const;
  bool visitNode(TCOD_bsp_t *node, void *userData);

 private:
  Tile *tiles;

  int roomNum = 0;   // room number
  int lastx, lasty;  // center of the last room

  TCOD_map_t tcod_map;

  void dig(int x1, int y1, int x2, int y2);
  void createRoom(bool first, int x1, int y1, int x2, int y2);
};