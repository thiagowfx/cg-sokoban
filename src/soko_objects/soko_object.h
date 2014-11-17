
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
      This method should be overloaded for every SokoObject
      */
      virtual Type getType() = 0;
  };
}