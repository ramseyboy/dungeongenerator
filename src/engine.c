#include "engine.h"

bool callback_wrapper(TCOD_bsp_t *node, void *userData) {
  return map_visitNode(engine.map, node, userData);
}

void engine_init() {
  TCOD_console_init_root(80, 50, "Dungeon Generator", false, TCOD_RENDERER_SDL);

  engine.computeFov = true;
  engine.fovRadius = 10;

  Actor *player = actor_new(40, 25, '@', TCOD_white);
  engine.player = player;
  
  vector_init(&engine.actors);
  vector_add(&engine.actors, player);

  engine.map = map_new(80, 45);

  // this should be moved to the map file
  TCOD_bsp_t *bsp = TCOD_bsp_new_with_size(0, 0, engine.map->width, engine.map->height);
  TCOD_bsp_split_recursive(bsp, NULL, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f,
                           1.5f);

  TCOD_bsp_traverse_pre_order(bsp, callback_wrapper, NULL);
}

void engine_free() {
  vector_free(&engine.actors);
  map_delete(engine.map);
}

void engine_update() {  
  TCOD_key_t key;
  TCOD_sys_check_for_event(TCOD_EVENT_KEY_PRESS, &key, NULL);
  switch (key.vk) {
    case TCODK_UP:
      if (!map_is_wall(engine.map, engine.player->x, engine.player->y - 1)) {
        engine.player->y--;
        engine.computeFov = true;
      }
      break;
    case TCODK_DOWN:
      if (!map_is_wall(engine.map, engine.player->x, engine.player->y + 1)) {
        engine.player->y++;
        engine.computeFov = true;
      }
      break;
    case TCODK_LEFT:
      if (!map_is_wall(engine.map, engine.player->x - 1, engine.player->y)) {
        engine.player->x--;
        engine.computeFov = true;
      }
      break;
    case TCODK_RIGHT:
      if (!map_is_wall(engine.map, engine.player->x + 1, engine.player->y)) {
        engine.player->x++;
        engine.computeFov = true;
      }
      break;
    default:
      break;
  }
  if (engine.computeFov) {
    map_compute_fov(engine.map);
    engine.computeFov = false;
  }
}

void engine_render() {
  TCOD_console_clear(NULL);
  // draw the map
  map_render(engine.map);
  // draw the actors
  int size = vector_total(&engine.actors);
  for (int i = 0; i < size; i++) {
    Actor *actor = (Actor *) vector_get(&engine.actors, i);
    if (map_is_in_fov(engine.map, actor->x, actor->y)) {
      actor_render(actor);
    }
  }
}

bool is_window_closed() {
  return TCOD_console_is_window_closed();
}

void flush() {
  TCOD_console_flush();
}
