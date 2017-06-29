#pragma once

#include "libtcod.h"

static const int ROOM_MAX_SIZE = 12;
static const int ROOM_MIN_SIZE = 6;

typedef struct Tile {
  bool explored;  // has the player already seen this tile ?
} Tile;

typedef struct Map {
  int width, height;

  Tile *tiles;

  int roomNum;   // room number
  int lastx, lasty;  // center of the last room

  TCOD_map_t tcod_map;
} Map;

Map *map_new(int width, int height);

void map_delete(Map *map);

bool map_is_wall(Map *map, int x, int y);

bool map_is_in_fov(Map *map, int x, int y);

bool map_is_explored(Map *map, int x, int y);

void map_compute_fov(Map *map);

void map_render(Map *map);

bool map_visitNode(Map *map, TCOD_bsp_t *node, void *userData);

void map_dig(Map *map, int x1, int y1, int x2, int y2);

void map_create_room(Map *map, bool first, int x1, int y1, int x2, int y2);