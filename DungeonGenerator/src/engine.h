#pragma once

#include "libtcod.hpp"
#include "actor.h"
#include "map.h"

class Engine {
 public:
  Engine();
  ~Engine();
  void update();
  void render();

 private:
  TCODList<Actor *> actors;
  Actor *player;
  Map *map;
};