#include "engine.h"

// this should be moved to the map file and deleted once converted to an all C project
extern "C" unsigned char callback_wrapper(TCOD_bsp_t *node, void *userData) {
  return engine.map->visitNode(node, userData);
}

Engine::Engine() : fovRadius(10), computeFov(true) {
  TCOD_console_init_root(80, 50, "Dungeon Generator", false, TCOD_RENDERER_SDL);
  
  player = actor_new(40, 25, '@', TCOD_white);
  actors.push_back(player);
  
  map = new Map(80, 45);

  // this should be moved to the map file
  TCOD_bsp_t *bsp = TCOD_bsp_new_with_size(0, 0, map->width, map->height);
  TCOD_bsp_split_recursive(bsp, NULL, 8, Map::ROOM_MAX_SIZE, Map::ROOM_MAX_SIZE, 1.5f,
                           1.5f);
  TCOD_bsp_traverse_pre_order(bsp, callback_wrapper, NULL);
}

Engine::~Engine() {
  actors.clear();
  delete map;
}

void Engine::update() {
  TCOD_key_t key;
  TCOD_sys_check_for_event(TCOD_EVENT_KEY_PRESS, &key, NULL);
  switch (key.vk) {
    case TCODK_UP:
      if (!map->isWall(player->x, player->y - 1)) {
        player->y--;
        computeFov = true;
      }
      break;
    case TCODK_DOWN:
      if (!map->isWall(player->x, player->y + 1)) {
        player->y++;
        computeFov = true;
      }
      break;
    case TCODK_LEFT:
      if (!map->isWall(player->x - 1, player->y)) {
        player->x--;
        computeFov = true;
      }
      break;
    case TCODK_RIGHT:
      if (!map->isWall(player->x + 1, player->y)) {
        player->x++;
        computeFov = true;
      }
      break;
    default:
      break;
  }
  if (computeFov) {
    map->computeFov();
    computeFov = false;
  }
}

void Engine::render() {
  TCOD_console_clear(NULL);
  // draw the map
  map->render();
  // draw the actors
  for (std::vector<Actor *>::iterator it = actors.begin(); it != actors.end();
       ++it) {
    Actor *actor = *it;
    if (map->isInFov(actor->x, actor->y)) {
      actor_render(actor);
    }
  }
}
