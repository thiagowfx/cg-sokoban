#ifndef _SOKO_BOARD_H_
#define _SOKO_BOARD_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include "soko_position.hpp"
#include "soko_object.hpp"
#include "soko_dynamic_object.hpp"
using namespace std;

namespace Sokoban {
  /** 
  This class represents a Sokoban board.  
  */
  class SokoBoard {
    private:
      /// This nested class represents a movement from a caracter and/or a box
      class SokoMovement {
        public:
          SokoMovement(Direction direction, int boxMoved = -1) : direction(direction), 
                                                           boxMoved(boxMoved) {};
          /// The direction of the movement
          Direction direction;

          /// Index of the box moved with this movement;
          int boxMoved;
      };

    public:

      /// Constructs a new SokoBoard from @filename.
      SokoBoard(std::string filename);

      /// Move the character to direction indicated by @direction.      
      int move(Direction direction);

      /// Prints a representation of this class to a ostream.
      friend ostream& operator<<(ostream&, SokoBoard&);

      /// Return the string representation of this object.
      std::string toString();

      /// Get the number of moves of the character so far.
      unsigned getNumberOfMoves() const;

      /// Get the number of boxes of this board.
      unsigned getNumberOfBoxes() const;

      /// Get the number of light boxes of this board.
      unsigned getNumberOfLightBoxes() const;

      /// Get the number of heavy boxes of this board.
      unsigned getNumberOfHeavyBoxes() const;

      /// Get the number of targets of this board.
      unsigned getNumberofTargets() const;

      /// Get the number of boxes not yet moved to a target in this board.
      unsigned getNumberOfUnresolvedBoxes() const;

      /// Get the number of light boxes not yet moved to a target in this board.
      unsigned getNumberOfUnresolvedLightBoxes() const;

      /// Get the number of heavy boxes not yet moved to a target in this board.
      unsigned getNumberOfUnresolvedHeavyBoxes() const;

      /// Return the number of rows of the static board.
      unsigned getNumberOfRows() const;

      /// Return the number of columns of the static board.
      unsigned getNumberOfColumns() const;

      /// Returns true if this board is finished, with all boxes moved to targets.
      bool isFinished() const;

      /// Returns the element in position x, y of the dynamic board.
      std::vector< SokoDynamicObject > getDynamic();

      
      // Returns the element in position x, y of the dynamic board.
      SokoDynamicObject getDynamic(int x, int y);

      /// Returns the element in position x, y of the static board.
      SokoObject getStatic(int x, int y) const;

      /// Undo the last character movement.
      int undo();

      /// Updates all the elements in the board for a time t
      void update(double t);

    private:
      unsigned unresolvedLightBoxes, unresolvedHeavyBoxes, 
        lightBoxes, heavyBoxes, targets;

      /// The stack with all the movements that happened.
      std::stack< SokoMovement > undoTree;

      /// The character position.
      //SokoPosition characterPosition;

      /// The character index.
      int characterIndex;

      /// The direction the character is facing.
      Direction characterDirection;
      
      /// Stores dynamic SokoObjects of a board, such as boxes and the character.
      std::vector< SokoDynamicObject > dynamicBoard;
      
      /// Stores static SokoObjects of a board, such as walls and targets.
      std::vector< std::vector< SokoObject > > staticBoard;

      /// Update how many boxes are (un)resolved.
      void updateUnresolvedBoxes();

      /// Setting all the dynamic objects indexes
      void setDynamicIndexes();
  };
}

#endif // _SOKO_BOARD_H_
