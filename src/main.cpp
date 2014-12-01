#include <iostream>
#include "gui.hpp"
using namespace Sokoban;

/// This function starts the game in ASCII mode. Useful for testing, but not so funny. =/
void startASCIIMode();

/// Print useful information about the game.
void usage() {
  std::cout << ".----------------. .----------------. .----------------. .----------------. \n| .--------------. | .--------------. | .--------------. | .--------------. |\n| | _____  _____ | | |  _________   | | |  _______     | | |     _____    | |\n| ||_   _||_   _|| | | |_   ___  |  | | | |_   __ \\    | | |    |_   _|   | |\n| |  | |    | |  | | |   | |_  \\_|  | | |   | |__) |   | | |      | |     | |\n| |  | '    ' |  | | |   |  _|      | | |   |  __ /    | | |   _  | |     | |\n| |   \\ `--' /   | | |  _| |_       | | |  _| |  \\ \\_  | | |  | |_' |     | |\n| |    `.__.'    | | | |_____|      | | | |____| |___| | | |  `.___.'     | |\n| |              | | |              | | |              | | |              | |\n| '--------------' | '--------------' | '--------------' | '--------------' |\n '----------------' '----------------' '----------------' '----------------' " << std::endl;
  std::cout << "Developed by:" << std::endl;
  std::cout << "\tThiago Barroso Perrotta" << std::endl;
  std::cout << "\tFelipe Podolan Oliveira" << std::endl;
  std::cout << "\tPedro Cruz Caminha" << std::endl;
  std::cout << std::endl;
  std::cout << "Copyright (C) 2014" << std::endl;
  std::cout << "This program is distributed under a MIT License." << std::endl;
  std::cout << "Its source code is available at:" << std::endl;
  std::cout << "\t" << "https://github.com/thiagowfx/cg-sokoban" << std::endl;

  std::cout << std::endl;
  std::cout << "How to play it:" << std::endl;
  std::cout << "\t- use the directional keys to move the character" << std::endl;
  std::cout << "\t- use the 'r' key to restart the current level" << std::endl;
  std::cout << "\t- use the 'u' key to undo your last move" << std::endl;
  std::cout << "\t- use the 'm' key to mute the background music" << std::endl;
  std::cout << "\t- use the 'q' or the 'ESC' key to quit from the game at any moment" << std::endl;
}

int main(int argc, char** argv) {
  if (argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help") || !strcmp(argv[1], "-v"))) {
    usage();
    return EXIT_SUCCESS;
  }

  Sokoban::Gui *gui = new Sokoban::Gui();
  gui->gameLoop();
  // startASCIIMode();
  return EXIT_SUCCESS;
}

void startASCIIMode() {
  SokoBoard board("../assets/stages/stage1.sok");
  bool go = true;
  char command;
  while(go) {
    cout << board.toString();
    cout << endl << "======== HELP ========" << endl;
    cout << endl << "up: w; down: s; right: d; left: a " << endl;
    cin >> command;
    switch(command) {
    case 'w':
      board.move(Direction::UP);
      break;
    case 's':
      board.move(Direction::DOWN);
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
}
