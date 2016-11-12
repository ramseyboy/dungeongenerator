#pragma once

#include <vector>
#include "actor.h"
#include "map.h"

class Engine {
 public:
  Actor *player;
  std::vector<Actor *> actors;
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