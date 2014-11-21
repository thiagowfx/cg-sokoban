#ifndef SOKOBAN_SOKO_OBJECT
#define SOKOBAN_SOKO_OBJECT

namespace Sokoban {
  /**
  This class represents an object that is on a sokoban board
  */
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

      /**
      Creates an empty SokoObject
      */
      SokoObject() {};

      /**
      Creates a SokoObject with the especific type
      */
      SokoObject(Type _type) : type(_type) { };

      /**
      Creates a Character object
      */
      SokoObject(Direction _facing) : type(CHARACTER), facing(_facing) { };

      /**
      Represents the direction the object is facing
      */
      Direction facing;

      Type getType() const { return type; };
  protected:
    Type type;
  };
}

#endif
