#ifndef SOKOBAN_POSITION
#define SOKOBAN_POSITION


#include "direction.hpp"
namespace Sokoban {
  /**
  This class represents a position on a sokoban board
  */
  class Position {
    public:
      Position() : x(0), y(0) { } ;
      Position(Direction direction) {
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

      Position(int _x, int _y) : x(_x), y(_y) { };
      Position operator+(Position other) { return Position( x + other.x, y + other.y); }
      int x, y;

  };
}  //Sokoban

#endif