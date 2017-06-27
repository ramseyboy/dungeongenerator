#pragma once

#include "libtcod.h"

typedef struct Actor {
  int x, y;          // position on map
  char ch;            // ascii code
  TCOD_color_t col;  // color
} Actor;

Actor *actor_new(int x, int y, char ch, TCOD_color_t col); 

void actor_delete(Actor *actor);

void actor_render(Actor *actor);
