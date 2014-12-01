#ifndef _SOKO_DYNAMIC_OBJECT_H_
#define _SOKO_DYNAMIC_OBJECT_H_

#include "soko_object.hpp"
#include "soko_position.hpp"
#include <iostream>

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
                       SokoObject(type), position(position_) { 
                       	positionX = position_.x;
                       	positionY = position_.y; };
      
      /// The x position of this object on 2d free space
      double positionX;
      
      /// The x position of this object on 2d free space
      double positionY;

      SokoPosition position;
      SokoPosition lastPosition;

      int getIndex() { return index; };

      void move(double step){
      	double dX = position.x;
      	double dY = position.y;
      	if((positionX > dX+0.01 && positionX < dX - 0.01) || 
      		(positionY > dY+0.01 && positionY < dY - 0.01)) {
          positionX = positionX + (lastPosition.x - position.x)*step;
          positionY = positionY + (lastPosition.y - position.y)*step;
      	}

      	/*positionX = (double) position.x;
      	positionY = (double) position.y;*/
      };

      /// The index of this object in the Dynamic board
      int index;

      void updatePosition(SokoPosition newPosition) {
      	lastPosition = position;
      	position = newPosition;
      }
  };
}

#endif // _SOKO_OBJECT_H_