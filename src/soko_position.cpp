#include "soko_position.hpp"

namespace Sokoban {

SokoPosition::SokoPosition() :
  x(0),
  y(0) {}

SokoPosition::SokoPosition(int x, int y) :
  x(x),
  y(y) {}

SokoPosition::SokoPosition(const Direction& direction) {
  switch(direction) {
  case Direction::UP:
    x = 0;
    y = 1;
    break;
  case Direction::LEFT:
    x = -1;
    y = 0;
    break;
  case Direction::DOWN:
    x = 0;
    y = -1;
    break;
  case Direction::RIGHT:
    x = 1;
    y = 0;
    break;
  }
}

SokoPosition SokoPosition::operator+(const SokoPosition& other) {
  return SokoPosition(x + other.x, y + other.y);
}

}
