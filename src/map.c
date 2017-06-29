#include "map.h"
#include "engine.h"
#include "random.h"

Map *map_new(int width, int height) {
  Map *map;
  map = (Map *)malloc(sizeof(*map));

  map->width = width;
  map->height = height;

  int length = width * height;
  Tile *tiles = (Tile *)malloc(length * sizeof(Tile));

  for (int i = 0; i < length; i++) {
    tiles[i].explored = false;
  }

  map->tiles = tiles;

  map->tcod_map = TCOD_map_new(width, height);

  return map;
}

void map_delete(Map *map) {
  free(map->tiles);
  TCOD_map_delete(map->tcod_map);
  free(map);
}

bool map_is_wall(Map *map, int x, int y) {
  return !TCOD_map_is_walkable(map->tcod_map, x, y);
}

bool map_is_explored(Map *map, int x, int y) {
  return map->tiles[x + y * map->width].explored;
}

bool map_is_in_fov(Map *map, int x, int y) {
  if (TCOD_map_is_in_fov(map->tcod_map, x, y)) {
    map->tiles[x + y * map->width].explored = true;
    return true;
  }
  return false;
}

void map_compute_fov(Map *map) {
  TCOD_map_compute_fov(map->tcod_map, engine.player->x, engine.player->y,
                       engine.fovRadius, /*light walls*/ false, FOV_BASIC);
}

void map_render(Map *map) {
  static const TCOD_color_t darkWall = TCOD_color_RGB(0, 0, 100);
  static const TCOD_color_t darkGround = TCOD_color_RGB(50, 50, 150);
  static const TCOD_color_t lightWall = TCOD_color_RGB(130, 110, 50);
  static const TCOD_color_t lightGround = TCOD_color_RGB(200, 180, 50);

  for (int x = 0; x < map->width; x++) {
    for (int y = 0; y < map->height; y++) {
      if (map_is_in_fov(map, x, y)) {
        if (map_is_wall(map, x, y)) {
          TCOD_console_set_char_background(NULL, x, y, lightWall,
                                           TCOD_BKGND_SET);
        } else {
          TCOD_console_set_char_background(NULL, x, y, lightGround,
                                           TCOD_BKGND_SET);
        }
      } else if (map_is_explored(map, x, y)) {
        if (map_is_wall(map, x, y)) {
          TCOD_console_set_char_background(NULL, x, y, darkWall,
                                           TCOD_BKGND_SET);
        } else {
          TCOD_console_set_char_background(NULL, x, y, darkGround,
                                           TCOD_BKGND_SET);
        }
      }
    }
  }
}

void map_dig(Map *map, int x1, int y1, int x2, int y2) {
  if (x2 < x1) {
    int tmp = x2;
    x2 = x1;
    x1 = tmp;
  }
  if (y2 < y1) {
    int tmp = y2;
    y2 = y1;
    y1 = tmp;
  }
  for (int tilex = x1; tilex <= x2; tilex++) {
    for (int tiley = y1; tiley <= y2; tiley++) {
      TCOD_map_set_properties(map->tcod_map, tilex, tiley, true, true);
    }
  }
}

void map_create_room(Map *map, bool first, int x1, int y1, int x2, int y2) {
  map_dig(map, x1, y1, x2, y2);
  if (first) {
    // put the player in the first room
    engine.player->x = (x1 + x2) / 2;
    engine.player->y = (y1 + y2) / 2;
  } else {
    if (generate(0, 3) == 0) {
      Actor *actor = actor_new((x1 + x2) / 2, (y1 + y2) / 2, '@', TCOD_yellow);
      vector_add(&engine.actors, actor);
    }
  }
}

bool map_visitNode(Map *map, TCOD_bsp_t *node, void *userData) {
  if (TCOD_bsp_is_leaf(node)) {
    int x, y, w, h;
    // dig a room
    w = generate(ROOM_MIN_SIZE, node->w - 2);
    h = generate(ROOM_MIN_SIZE, node->h - 2);
    x = generate(node->x + 1, node->x + node->w - w - 1);
    y = generate(node->y + 1, node->y + node->h - h - 1);

    map_create_room(map, map->roomNum == 0, x, y, x + w - 1, y + h - 1);

    if (map->roomNum != 0) {
      // dig a corridor from last room
      map_dig(map, map->lastx, map->lasty, x + w / 2, map->lasty);
      map_dig(map, x + w / 2, map->lasty, x + w / 2, y + h / 2);
    }
    map->lastx = x + w / 2;
    map->lasty = y + h / 2;
    map->roomNum++;
  }
  return true;
}