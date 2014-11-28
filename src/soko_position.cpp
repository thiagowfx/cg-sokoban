#include "soko_position.hpp"

namespace Sokoban {

SokoPosition::SokoPosition() :
  x(0),
  y(0) {}

SokoPosition::SokoPosition(int x, int y) :
  x(x),
  y(y) {}

SokoPosition SokoPosition::operator+(const Direction& direction) const {
  switch(direction) {

  case Direction::UP:
    return SokoPosition(x, y - 1);

  case Direction::LEFT:
    return SokoPosition(x - 1, y);

  case Direction::DOWN:
    return SokoPosition(x, y + 1);

  case Direction::RIGHT:
    return SokoPosition(x + 1, y);

  default:
    return SokoPosition(x,y);
  }
}

SokoPosition SokoPosition::operator-(const Direction& direction) const {
  switch(direction) {

  case Direction::UP:
    return SokoPosition(x, y + 1);

  case Direction::LEFT:
    return SokoPosition(x + 1, y);

  case Direction::DOWN:
    return SokoPosition(x, y - 1);

  case Direction::RIGHT:
    return SokoPosition(x - 1, y);

  default:
    return SokoPosition(x,y);
  }
}

std::string SokoPosition::toString() const {
  std::stringstream ss;
  ss << "(" << x << "," << y << ")" << std::endl;
  return ss.str();
}

std::ostream& operator<<(std::ostream& os, const SokoPosition& s) {
  os << s.toString();
  return os;
}

}
