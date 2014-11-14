#include "gui.hpp"

int main(int argc, char** argv) {
  Gui *gui = new Gui();
  gui->gameLoop();
  return EXIT_SUCCESS;
}
