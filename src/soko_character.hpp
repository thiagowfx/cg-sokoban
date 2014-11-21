#ifndef SOKOBAN_SOKO_CHARACTER
#define SOKOBAN_SOKO_CHARACTER

#include "soko_object.hpp"
#include "soko_direction.hpp"

namespace Sokoban {
  /**
  This class represents an object that is on a sokoban board
  */
  class SokoCharacter : SokoObject {
    public:
      /**
      Creates an empty SokoCharacter
      */
      SokoCharacter() : SokoObject(CHARACTER) { };

      /**
      Creates an empty SokoObject
      */
      SokoCharacter(Direction _facing) : SokoObject(CHARACTER), facing(_facing) { };

      /**
      Represents the direction the character is facing
      */
      Direction facing;
  private:
  };
}

#endif