#include "soko_object.h"
namespace Sokoban {
  /**
  This class represents an object that is a heavy box on a sokoban board
  */
  class SokoHeavyBox : SokoObject {
    public:

      /**
      This method returns the type of this SokoObject
      */
      virtual Type getType() {
        return HEAVY_BOX;
      }
  };
}