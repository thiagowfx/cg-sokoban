#ifndef _SOKO_CHARACTER_H_
#define _SOKO_CHARACTER_H_

#include "soko_direction.hpp"
#include "soko_object.hpp"

namespace Sokoban {
  /** This class represents an object that is on a sokoban board. */
  class SokoCharacter : SokoObject {
    public:
      SokoCharacter() : SokoObject(CHARACTER) {};

      /** Creates an empty SokoObject. */
      SokoCharacter(Direction facing) : SokoObject(CHARACTER), facing(facing) {};

      /** Represents the direction the character is facing. */
      Direction facing;
  };
}

#endif // _SOKO_CHARACTER_H_
