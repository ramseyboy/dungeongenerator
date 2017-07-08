#include "engine.h"
#include "libtcod.h"

Engine engine;
int main(int argc, char* argv[]) {
  engine_init();
  while (!is_window_closed()) {
    engine_update();
    engine_render();
    flush();
  }
  engine_free();
  return 0;
}
