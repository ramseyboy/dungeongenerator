#include "map.h"
#include "engine.h"
#include "random.h"

Map::Map(int width, int height) : width(width), height(height) {
  tiles = new Tile[width * height];

  tcod_map = TCOD_map_new(width, height);
}

Map::~Map() {
  delete[] tiles;
  TCOD_map_delete(tcod_map);
}

bool Map::isWall(int x, int y) const {
  return !TCOD_map_is_walkable(tcod_map, x, y);
}

bool Map::isExplored(int x, int y) const {
  return tiles[x + y * width].explored;
}

bool Map::isInFov(int x, int y) const {
  if (TCOD_map_is_in_fov(tcod_map, x, y)) {
    tiles[x + y * width].explored = true;
    return true;
  }
  return false;
}

void Map::computeFov() {
  TCOD_map_compute_fov(tcod_map, engine.player->x, engine.player->y,
                       engine.fovRadius, /*light walls*/ false, FOV_BASIC);
}

void Map::render() const {
  static const TCOD_color_t darkWall = TCOD_color_RGB(0, 0, 100);
  static const TCOD_color_t darkGround = TCOD_color_RGB(50, 50, 150);
  static const TCOD_color_t lightWall = TCOD_color_RGB(130, 110, 50);
  static const TCOD_color_t lightGround = TCOD_color_RGB(200, 180, 50);

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      if (isInFov(x, y)) {
        if (isWall(x, y)) {
          TCOD_console_set_char_background(NULL, x, y, lightWall,
                                           TCOD_BKGND_SET);
        } else {
          TCOD_console_set_char_background(NULL, x, y, lightGround,
                                           TCOD_BKGND_SET);
        }
      } else if (isExplored(x, y)) {
        if (isWall(x, y)) {
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

void Map::dig(int x1, int y1, int x2, int y2) {
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
      TCOD_map_set_properties(tcod_map, tilex, tiley, true, true);
    }
  }
}

void Map::createRoom(bool first, int x1, int y1, int x2, int y2) {
  dig(x1, y1, x2, y2);
  if (first) {
    // put the player in the first room
    engine.player->x = (x1 + x2) / 2;
    engine.player->y = (y1 + y2) / 2;
  } else {
    if (generate(0, 3) == 0) {
      Actor *actor = actor_new((x1 + x2) / 2, (y1 + y2) / 2, '@', TCOD_yellow);
      engine.actors.push_back(actor);
    }
  }
}

bool Map::visitNode(TCOD_bsp_t *node, void *userData) {
  if (TCOD_bsp_is_leaf(node)) {
    int x, y, w, h;
    // dig a room
    w = generate(ROOM_MIN_SIZE, node->w - 2);
    h = generate(ROOM_MIN_SIZE, node->h - 2);
    x = generate(node->x + 1, node->x + node->w - w - 1);
    y = generate(node->y + 1, node->y + node->h - h - 1);

    createRoom(roomNum == 0, x, y, x + w - 1, y + h - 1);

    if (roomNum != 0) {
      // dig a corridor from last room
      dig(lastx, lasty, x + w / 2, lasty);
      dig(x + w / 2, lasty, x + w / 2, y + h / 2);
    }
    lastx = x + w / 2;
    lasty = y + h / 2;
    roomNum++;
  }
  return true;
}