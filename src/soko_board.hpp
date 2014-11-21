#ifndef _SOKO_BOARD_H_
#define _SOKO_BOARD_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "helpers.hpp"
#include "soko_position.hpp"
#include "soko_position.hpp"
#include "soko_object.hpp"
using namespace std;

namespace Sokoban {
  /** This class represents a Sokoban board. */
  class SokoBoard {
    public:
      SokoBoard(const char* filename);

      /* Move the character to direction indicated by @direction. */
      void move(Direction direction); // TODO

      friend ostream& operator<<(ostream&, const SokoBoard&);
      std::string toString() const;
      unsigned getNumberOfBoxes() const;
      unsigned getNumberofTargets() const;
      unsigned getNumberOfUnresolvedBoxes() const;

  public:
      std::vector< std::vector<SokoObject> > dynamicBoard;
      std::vector< std::vector<SokoObject> > staticBoard;

    private:
      unsigned unresolvedBoxes, boxes = 0, targets = 0;
      SokoPosition characterPosition;
  };
}

#endif // _SOKO_BOARD_H_
