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
                       	positionY = position_.y;
                        progress = 1.0; };
      
      /// The x position of this object on 2d free space
      double positionX;
      
      /// The x position of this object on 2d free space
      double positionY;

      SokoPosition position;
      SokoPosition lastPosition;

      int getIndex() { return index; };

      void move(double step) {
      	//double dX = (lastPosition.x - position.x)*0.1;
      	//double dY = (lastPosition.y - position.y)*0.1;
        progress +=step;
        
        if(progress < 1.0) {
          positionX = (1.0-progress) * lastPosition.x + (progress * position.x);
          positionY = (1.0-progress) * lastPosition.y + (progress * position.y);
        }

      };

      /// The index of this object in the Dynamic board
      int index;

      void updatePosition(SokoPosition newPosition) {
      	positionX = position.x;
      	positionY = position.y;
      	lastPosition = position;
      	position = newPosition;
        progress = 0.0;
      }

    private:
      double progress;
  };
}

#endif // _SOKO_OBJECT_H_