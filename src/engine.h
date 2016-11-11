#pragma once

#include <vector>
#include "actor.h"
#include "map.h"

class Engine {
 public:
  Actor *player;
  std::vector<Actor *> actors;  
  Map *map;

  Engine();
  ~Engine();
  void update();
  void render();
};

extern Engine engine;