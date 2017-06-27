#pragma once

#include "libtcod.h"

class Actor {
 public:
  int x, y;          // position on map
  int ch;            // ascii code
  TCOD_color_t col;  // color

  Actor(int x, int y, int ch, const TCOD_color_t &col);
  void render() const;
};
