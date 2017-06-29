#include "engine.h"

extern "C" unsigned char callback_wrapper(TCOD_bsp_t *node, void *userData) {
  return map_visitNode(engine.map, node, userData);
}

Engine::Engine() : fovRadius(10), computeFov(true) {
  TCOD_console_init_root(80, 50, "Dungeon Generator", false, TCOD_RENDERER_SDL);

  player = actor_new(40, 25, '@', TCOD_white);
  actors.push_back(player);

  map = map_new(80, 45);

  // this should be moved to the map file
  TCOD_bsp_t *bsp = TCOD_bsp_new_with_size(0, 0, map->width, map->height);
  TCOD_bsp_split_recursive(bsp, NULL, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f,
                           1.5f);

  TCOD_bsp_traverse_pre_order(bsp, callback_wrapper, NULL);
}

Engine::~Engine() {
  actors.clear();
  map_delete(map);
}

void Engine::update() {
  TCOD_key_t key;
  TCOD_sys_check_for_event(TCOD_EVENT_KEY_PRESS, &key, NULL);
  switch (key.vk) {
    case TCODK_UP:
      if (!map_is_wall(map, player->x, player->y - 1)) {
        player->y--;
        computeFov = true;
      }
      break;
    case TCODK_DOWN:
      if (!map_is_wall(map, player->x, player->y + 1)) {
        player->y++;
        computeFov = true;
      }
      break;
    case TCODK_LEFT:
      if (!map_is_wall(map, player->x - 1, player->y)) {
        player->x--;
        computeFov = true;
      }
      break;
    case TCODK_RIGHT:
      if (!map_is_wall(map, player->x + 1, player->y)) {
        player->x++;
        computeFov = true;
      }
      break;
    default:
      break;
  }
  if (computeFov) {
    map_compute_fov(map);
    computeFov = false;
  }
}

void Engine::render() {
  TCOD_console_clear(NULL);
  // draw the map
  map_render(map);
  // draw the actors
  for (std::vector<Actor *>::iterator it = actors.begin(); it != actors.end();
       ++it) {
    Actor *actor = *it;
    if (map_is_in_fov(map, actor->x, actor->y)) {
      actor_render(actor);
    }
  }
}
