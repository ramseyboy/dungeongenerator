#pragma once

struct Tile {
  bool explored; // has the player already seen this tile ?
  Tile() : explored(false) {}
};