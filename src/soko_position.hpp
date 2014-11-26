#ifndef _SOKO_POSITION_H_
#define _SOKO_POSITION_H_

namespace Sokoban {
   /**
  Represents directions that boxes and the character might move.
  */
  typedef enum Direction {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
  } Direction;

  /** 
  This class represents a position on a sokoban board. 
  */
  class SokoPosition {
    public:
      /// Constructs a new SokoPosition.
      SokoPosition();

      /// Constructs a new SokoPosition on (x,y).
      SokoPosition(int x, int y);

      /// Return a new SokoPosition, moved on the specified direction.
      SokoPosition operator+(const Direction&) const;

      /// Return a new SokoPosition, moved on the specified direction.
      SokoPosition operator-(const Direction&) const;

      /// The coordinates (x,y) of this position.
      int x, y;
  };
}

#endif // _SOKO_POSITION_H_
