#pragma once

#include "vector.h"
#include "actor.h"
#include "map.h"

class Engine {
 public:
  Actor *player;
  Vector actors;
  Map *map;
  int fovRadius;

  Engine();
  ~Engine();
  void update();
  void render();

 private:
  bool computeFov;
};

extern Engine engine;