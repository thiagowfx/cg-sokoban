#ifndef SOKOBAN_SOKO_BOARD
#define SOKOBAN_SOKO_BOARD

#include <vector>
#include <string>
#include "direction.hpp"
#include "position.hpp"
#include "soko_object.h"

namespace Sokoban {
  /**
  This class represents an object that is on a sokoban board
  */
  class SokoBoard {
    public:
      /**
      Builds the boards from a file named filename;
      */
      SokoBoard(std::string filename);
      /**
      Move the character to direction indicated by @direction.
      */
      void move(Direction direction);
      /**
      Returns the number of boxes that are still out of a target.
      */
      int getUnsolvedBoxesNumber();

      /**
      Returns a string representation of the object
      */
      std::string toString();
      /**
      Prints the object on std out
      */
      void print();
    private:
      int unsolvedBoxesCounter;
      std::vector< std::vector<SokoObject> > dynamicBoard;
      std::vector< std::vector<SokoObject> > staticBoard;
      Position characterPosition;
  };
}  //Sokoban

#endif