#include "engine.h"
#include "libtcod.h"

Engine engine;
int main(int argc, char* argv[]) {
  engine_init();
  while (!TCOD_console_is_window_closed()) {
    engine_update();
    engine_render();
    TCOD_console_flush();
  }
  engine_free();
  return 0;
}
