#pragma once

struct Tile {
  bool canWalk;  // can we walk through this tile?
  Tile() : canWalk(true) {}
};