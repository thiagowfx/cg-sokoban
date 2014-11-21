#ifndef _SOKO_OBJECT_H_
#define _SOKO_OBJECT_H_

#include "helpers.hpp"

namespace Sokoban {
  /** This class represents an object that is on a sokoban board. */
  class SokoObject {
    public:
      typedef enum Type {
        EMPTY = 0,
        CHARACTER = 1,
        LIGHT_BOX = 2,
        HEAVY_BOX = 3,
        WALL = 4,
        TARGET = 5
      } Type;

    protected:
    Type type;

    public:
      SokoObject();
      SokoObject(const Type& type);
      /** Creates a Character object. */
      SokoObject(Direction facing);

      /** Represents the direction the object is facing. */
      Direction facing;
      Type getType() const;
  };
}

#endif // _SOKO_OBJECT_H_
