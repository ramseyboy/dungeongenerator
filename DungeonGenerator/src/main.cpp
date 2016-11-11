#include "libtcod.hpp"
#include "engine.h"

int main() {
  Engine *engine = new Engine();
  while (!TCODConsole::isWindowClosed()) {
    engine->update();
    engine->render();
    TCODConsole::flush();
  }
  delete engine;
  return 0;
}
