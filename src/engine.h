#pragma once

#include "libtcod.hpp"
#include "actor.h"
#include "map.h"

class Engine {
 public:
  Actor *player;
  TCODList<Actor *> actors;
  Map *map;

  Engine();
  ~Engine();
  void update();
  void render();
};

extern Engine engine;