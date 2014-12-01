#ifndef _SOKO_DYNAMIC_OBJECT_H_
#define _SOKO_DYNAMIC_OBJECT_H_

#include "soko_object.hpp"
#include "soko_position.hpp"

namespace Sokoban {
  /**
  This class represents a dynamic object that is on a sokoban board. 
  */
  class SokoDynamicObject : public SokoObject {
    public:
      /// Constructs an empty SokoObject.
      SokoDynamicObject() { };

      /// Constructs a SokoObject with the given type.
      SokoDynamicObject(const Type& type) :
                       SokoObject(type) { };

      /// Constructs a new SokoObject of this given @type and @position.
      SokoDynamicObject(const Type& type, const SokoPosition position_) :
                       SokoObject(type), position(position_) { };

/*	  /// Constructs a new SokoObject of this given @type and coordinates. 
	  SokoDynamicObject(const Type& type, double x, double y) : 
	                    SokoObject(type), positionX(x), positionY(y) {};*/
      
      /// The x position of this object on 2d free space
      double positionX;
      
      /// The x position of this object on 2d free space
      double positionY;

      SokoPosition position;

      int getIndex() { return index; };

      /// The index of this object in the Dynamic board
      int index;
  };
}

#endif // _SOKO_OBJECT_H_