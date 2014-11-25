#include <iostram>
#include "gui.hpp"

int main(int argc, char** argv) {
  Gui *gui = new Gui();
  gui->gameLoop();
  return EXIT_SUCCESS;
}


/**
This function starts the game in ASCII mode. Useful for testing, but not so funny =/
*/
void startASCIIMode() {
  SokoBoard board("map1.soko");
  bool go = true;
  char command;
  while(go) {
    cout << board.toString();
    cout << endl << "======== HELP ========" << endl;
    cout << endl << "up: w; down: s; right: d; left: a " << endl;
    cin >> command;
    switch(command) {
    case 'w':
      board.move(Direction::DOWN);  // Yes, up and down are inverted. Your life is a lie.
      break;
    case 's':
      board.move(Direction::UP);
      break;
    case 'd':
      board.move(Direction::RIGHT);
      break;
    case 'a':
      board.move(Direction::LEFT);
      break;
    case 'e':
      go = false;
      break;
    default:
      break;
    }
  }
  system("pause");
  return 0;
}
