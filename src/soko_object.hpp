#ifndef _SOKO_OBJECT_H_
#define _SOKO_OBJECT_H_

#include "soko_position.hpp"

namespace Sokoban {
  /**
  This class represents an object that is on a sokoban board. 
  */
  class SokoObject {
    public:
      /** The type of this SokoObject. */
      typedef enum Type {
        EMPTY = 0,      // an empty position
        CHARACTER = 1,  // the character
        LIGHT_BOX = 2,  // a box with a light weight
        HEAVY_BOX = 3,  // a box with a heavy height
        WALL = 4,       // a wall
        TARGET = 5      // a position where boxes should be moved to
      } Type;

    protected:
    /**
    The type of this SokoObject.
    */
    Type type;

    public:
      /**
      Constructs a new SokoObject.
      */
      SokoObject();

      /**
      Constructs a new SokoObject of this given @type.
      */
      SokoObject(const Type& type);

      /**
      Creates a Character object.
      */
      SokoObject(Direction facing);

      /** 
      Represents the direction the object is facing. 
      */
      Direction facing;

      /**
      Return the type of this SokoObject.
      */
      Type getType() const;
  };
}

#endif // _SOKO_OBJECT_H_
