#include "libtcod.h"
#include "engine.h"

Engine engine;
int main(int argc, char* argv[]) {
  while (!TCOD_console_is_window_closed()) {
    engine.update();
    engine.render();
    TCOD_console_flush();
  }
  return 0;
}
