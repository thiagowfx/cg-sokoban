#include "soko_board.hpp"

namespace Sokoban {

SokoBoard::SokoBoard(std::string filename) : 
    lightBoxes(0), heavyBoxes(0), targets(0) {
  string line;
  ifstream mapFile(filename.c_str());

  if (mapFile.is_open()) {
    int x_now(0), y_now(0);

    // Read line-by-line
    while (getline(mapFile,line)) {
      vector<SokoObject> staticObjLine;
      istringstream streamLine(line);

      // Read a line
      while(!streamLine.eof()) {
        SokoObject staticObj;
        SokoDynamicObject dynamicObj;
        int i_type;

        streamLine >> i_type;
        SokoObject::Type type = SokoObject::Type(i_type);

        // Update counters
        if (type == SokoObject::LIGHT_BOX)
          lightBoxes++;
        else if (type == SokoObject::HEAVY_BOX)
          heavyBoxes++;
        else if (type == SokoObject::TARGET)
          targets++;

        // Build both boards
        if(type == SokoObject::EMPTY || type == SokoObject::TARGET || type == SokoObject::WALL) {
          staticObj = SokoObject(type);
        }
        else {
          staticObj = SokoObject(SokoObject::EMPTY);
          dynamicObj = SokoDynamicObject(type, SokoPosition(x_now, y_now));
          dynamicBoard.push_back(dynamicObj);
        }
        staticObjLine.push_back(staticObj);
        x_now++;
      }

      staticBoard.push_back(staticObjLine);
      x_now = 0;
      y_now++;
    }
    unresolvedLightBoxes = lightBoxes;
    unresolvedHeavyBoxes = heavyBoxes;
    setDynamicIndexes();
    mapFile.close();
  }
  else {
    std::cout << "INFO: Unable to open file " << filename << std::endl;
  }
}

int SokoBoard::move(Direction direction) {
  int boxMovedIndex = -1, characterMoved = false;
  SokoPosition characterPosition = dynamicBoard[characterIndex].position;
  SokoPosition nextPosition = characterPosition + direction;

  // Checking out-of-bounds on y.
  if(nextPosition.y < 0 || nextPosition.y >= staticBoard.size())
    return false;

  // Checking out-of-bounds on x.
  if(nextPosition.x < 0 || nextPosition.x >= staticBoard[nextPosition.y].size())
    return false;

  if(staticBoard[nextPosition.y][nextPosition.x].getType() != SokoObject::WALL) {
    // CASE: Character movement only.
    SokoDynamicObject nextObj = getDynamic(nextPosition.x, nextPosition.y);

    if(nextObj.getType() == SokoObject::EMPTY) {
      dynamicBoard[characterIndex].updatePosition(nextPosition);
      characterMoved = true;
    }

    else { 
      SokoPosition boxNextPosition = nextPosition + direction;

      // Checking out-of-bounds on y.
      if(boxNextPosition.y < 0 || boxNextPosition.y >= staticBoard.size())
        return false;

      // Checking out-of-bounds on x.
      if(boxNextPosition.x < 0 || boxNextPosition.x >= staticBoard[nextPosition.y].size())
        return false;
      
      // CASE: box movement
      if(nextObj.getType() == SokoObject::LIGHT_BOX || 
        (nextObj.getType() == SokoObject::HEAVY_BOX && 
          unresolvedLightBoxes == 0)) { 
        SokoObject boxNextObj = getDynamic(boxNextPosition.x, boxNextPosition.y);

        if(boxNextObj.getType() == SokoObject::EMPTY &&
            staticBoard[boxNextPosition.y][boxNextPosition.x].getType() != SokoObject::WALL) {
          dynamicBoard[nextObj.index].updatePosition(boxNextPosition);
          dynamicBoard[characterIndex].updatePosition(nextPosition);
          characterMoved = true;
          boxMovedIndex = nextObj.index;
        }
      } 
    }
  }


  if(characterMoved) {
    undoTree.push(Movement(direction, boxMovedIndex));
    updateUnresolvedBoxes();
  }

  return boxMovedIndex;
}

int SokoBoard::undo() {
  if (!undoTree.empty()) {
    Movement last = undoTree.top();
    undoTree.pop();

    SokoPosition previousPosition = dynamicBoard[characterIndex].position - last.direction;
    dynamicBoard[characterIndex].resetPosition(previousPosition);
    
    if (last.boxMoved >= 0) {
      SokoPosition boxPosition = dynamicBoard[last.boxMoved].position - last.direction;
      dynamicBoard[last.boxMoved].resetPosition(boxPosition);
    }
    return last.boxMoved;
  }
  return -1;
}

std::string SokoBoard::toString() {
  std::stringstream ss;
  /*ss << "INFO: Dynamic Board: " << std::endl;
  for(auto line : dynamicBoard) {
    for(auto obj : line)
      ss << " " << obj.getType();
    ss << std::endl;
  }
  ss << std::endl;*/
  
  ss << "INFO: Board: " << std::endl;
  int x(0), y(0);
  for(auto line : staticBoard) {
    for(auto obj : line) {
      ss << " ";
      SokoDynamicObject dynObj = getDynamic(x, y);
      if(dynObj.getType() == SokoObject::EMPTY)
        ss << obj.getType();
      else
        ss << dynObj.getType();
      x++;
    }
    ss << std::endl;
    y++;
    x = 0;
  }
  ss << std::endl;

  ss << "INFO: Number of moves: " << getNumberOfMoves() << std::endl;
  ss << "INFO: Number of remaining light boxes: " << getNumberOfUnresolvedLightBoxes() << "/" << getNumberOfLightBoxes() << std::endl;
  ss << "INFO: Number of remaining heavy boxes: " << getNumberOfUnresolvedHeavyBoxes() << "/" << getNumberOfHeavyBoxes() << std::endl;
  ss << std::endl;

  for (auto obj : dynamicBoard) {
    ss << "Dynamic " << obj.getType() << " in position "<< obj.positionX << " ,"<< obj.positionY << std::endl;
    ss << "Dynamic " << obj.getType() << " lastposition "<< obj.lastPosition.x << " ,"<< obj.lastPosition.y << std::endl;
  }
  ss << std::endl; 
  return ss.str();
}

std::ostream& operator<<(std::ostream& os, SokoBoard& s) {
  os << s.toString();
  return os;
}

/** 
  Every test here is necessary (and done only when necessary).
  If you don't trust me, waste your time and please, increase the counter.
  Time wasted with these tests: 0.12 hours.
  */
void SokoBoard::updateUnresolvedBoxes() {
  unresolvedLightBoxes = lightBoxes;
  unresolvedHeavyBoxes = heavyBoxes;

  for(SokoDynamicObject dyn : dynamicBoard) {
    if(staticBoard[dyn.position.y][dyn.position.x].getType() == SokoObject::TARGET) {
      if(dyn.getType() == SokoObject::LIGHT_BOX)
        unresolvedLightBoxes--;
      if(dyn.getType() == SokoObject::HEAVY_BOX)    
        unresolvedHeavyBoxes--;
    }
  }
}

unsigned SokoBoard::getNumberOfMoves() const {
  return undoTree.size();
}

unsigned SokoBoard::getNumberOfBoxes() const {
  return lightBoxes + heavyBoxes;
}

unsigned SokoBoard::getNumberOfLightBoxes() const {
  return lightBoxes;
}

unsigned SokoBoard::getNumberOfHeavyBoxes() const {
  return heavyBoxes;
}

unsigned SokoBoard::getNumberofTargets() const {
  return targets;
}

unsigned SokoBoard::getNumberOfUnresolvedBoxes() const {
  return unresolvedLightBoxes + unresolvedHeavyBoxes;
}

unsigned SokoBoard::getNumberOfUnresolvedLightBoxes() const {
  return unresolvedLightBoxes;
}

unsigned SokoBoard::getNumberOfUnresolvedHeavyBoxes() const {
  return unresolvedHeavyBoxes;
}

bool SokoBoard::isFinished() const {
  return getNumberOfUnresolvedBoxes() == 0;
}

std::vector< SokoDynamicObject > SokoBoard::getDynamic() {
  return dynamicBoard;
}

SokoDynamicObject SokoBoard::getDynamic(int x, int y) {
  SokoDynamicObject empty(SokoObject::EMPTY, SokoPosition(x, y));
  for(auto obj : dynamicBoard) {
    if(obj.position.x == x && obj.position.y == y)
      return obj;
  }
  return empty;
}

SokoObject SokoBoard::getStatic(int x, int y) const {
  return staticBoard[y][x];
}

unsigned SokoBoard::getNumberOfRows() const {
  return staticBoard.size();
}

unsigned SokoBoard::getNumberOfColumns() const {
  return staticBoard[0].size();
}

void SokoBoard::setDynamicIndexes() {
  for(int i = 0; i < dynamicBoard.size(); i++) {
    dynamicBoard[i].index = i;
    if(dynamicBoard[i].getType() == SokoObject::CHARACTER)
      characterIndex = i;
  }
}

void SokoBoard::update(double t) {
  for(int i=0; i < dynamicBoard.size(); i++)
    dynamicBoard[i].move(t);
}

}
