#include <vector>
#include <string>
#include "direction.h"
#include "soko_objects/soko_object.h"

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
    private:
      int unsolvedBoxesCounter;
      std::vector< std::vector<SokoObject> > dynamicBoard;
      std::vector< std::vector<SokoObject> > staticBoard;
  };
}  //Sokoban