#include "soko_object.hpp"

namespace Sokoban {
  SokoObject::SokoObject() {}

  SokoObject::SokoObject(const Type& type) :
    type(type) {}

  SokoObject::Type SokoObject::getType() const {
    return type;
  }

  SokoObject::SokoObject(Direction facing) :
    type(CHARACTER),
    facing(facing) {};
}
