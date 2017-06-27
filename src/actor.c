#include "actor.h"

Actor *actor_new(int x, int y, char ch, TCOD_color_t col) {
  Actor *actor;
  actor = (Actor *)malloc(sizeof(*actor));
  actor->x = x;
  actor->y = y;
  actor->ch = ch;
  actor->col = col;
  return actor;
}

void actor_delete(Actor *actor) {
  free(actor);
}

void actor_render(Actor *actor) {
  TCOD_console_set_char(NULL, actor->x, actor->y, actor->ch);
  TCOD_console_set_char_foreground(NULL, actor->x, actor->y, actor->col);
}
