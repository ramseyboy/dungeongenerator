#include "actor.h"

Actor::Actor(int x, int y, int ch, const TCOD_color_t &col)
    : x(x), y(y), ch(ch), col(col) {}

void Actor::render() const {
  TCOD_console_set_char(NULL, x, y, ch);
  TCOD_console_set_char_foreground(NULL, x, y, col);
}
