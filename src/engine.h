#pragma once

#include "actor.h"
#include "map.h"
#include "vector.h"

typedef struct Engine {
  Actor *player;
  Vector actors;
  Map *map;
  int fovRadius;
  bool computeFov;
} Engine;

void engine_init();
void engine_free();

void engine_update();
void engine_render();

extern Engine engine;