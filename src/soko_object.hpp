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
      };

      /**
      Creates an empty SokoObject
      */
      SokoObject() {};

      /**
      Creates a SokoObject with the especific type
      */
      SokoObject(Type _type) : type(_type) { };
      /**
      This method should be overloaded for every SokoObject
      */
      Type getType() const { return type; };
  private:
    Type type;
  };
}

#endif