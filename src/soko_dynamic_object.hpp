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

      /// The position of this object on the board
      SokoPosition position;

      /// The last position of this object on the board
      SokoPosition lastPosition;

      int getIndex() { return index; };

      /// Moves the object with step. Step can be from 0.0 to 1.0
      void move(double step) {
        progress +=step;
        
        if(progress < 1.0) {
          positionX = (1.0-progress) * lastPosition.x + (progress * position.x);
          positionY = (1.0-progress) * lastPosition.y + (progress * position.y);
        }
      };

      /// The index of this object in the Dynamic board
      int index;

      /// Updates the position of the object
      void updatePosition(SokoPosition newPosition) {
      	positionX = position.x;
      	positionY = position.y;
      	lastPosition = position;
      	position = newPosition;
        progress = 0.0;
      }

      void resetPosition(SokoPosition newPosition) {
        positionX = newPosition.x;
        positionY = newPosition.y;
        position = newPosition;
        progress = 1.0;
      }

    private:
      double progress;
  };
}

#endif // _SOKO_OBJECT_H_