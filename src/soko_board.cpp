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
      vector<SokoObject> dynamicObjLine;
      istringstream streamLine(line);

      // Read a line
      while(!streamLine.eof()) {
        SokoObject staticObj;
        SokoObject dynamicObj;
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
          dynamicObj = SokoObject(SokoObject::EMPTY);
        }
        else {
          staticObj = SokoObject(SokoObject::EMPTY);
          dynamicObj = SokoObject(type);
          if(type == SokoObject::CHARACTER)
            characterPosition = SokoPosition(x_now, y_now);
        }
        staticObjLine.push_back(staticObj);
        dynamicObjLine.push_back(dynamicObj);
        x_now++;
      }

      staticBoard.push_back(staticObjLine);
      dynamicBoard.push_back(dynamicObjLine);
      x_now = 0;
      y_now++;
    }
    unresolvedLightBoxes = lightBoxes;
    unresolvedHeavyBoxes = heavyBoxes;
    mapFile.close();
  }
  else {
    cout << "Unable to open file " << filename.c_str() << endl;
  }
}

void SokoBoard::move(Direction direction) {
  bool boxMoved = false, characterMoved = false;

  SokoPosition nextPosition = characterPosition + direction;

  // Out-of-bounds on y.
  if(nextPosition.y < 0 || nextPosition.y >= staticBoard.size()) //checking if it is leaving the board y
    return;  // TODO: maybe do something

  // Out-of-bounds on x.
  if(nextPosition.x < 0 || nextPosition.x >= staticBoard[nextPosition.y].size()) //checking if it is leaving the board x
    return;  // TODO: maybe do something

  if(staticBoard[nextPosition.y][nextPosition.x].getType() != SokoObject::WALL) {

    // CASE: Character movement only.
    if(dynamicBoard[nextPosition.y][nextPosition.x].getType() == SokoObject::EMPTY) {
      dynamicBoard[nextPosition.y][nextPosition.x] = SokoObject(SokoObject::CHARACTER);
      dynamicBoard[characterPosition.y][characterPosition.x] = SokoObject(SokoObject::EMPTY);
      characterPosition = nextPosition;
      characterMoved = true;
    }

    // CASE: Light box movement
    else if(dynamicBoard[nextPosition.y][nextPosition.x].getType() == SokoObject::LIGHT_BOX) { 
      SokoPosition boxNextPosition = nextPosition + direction;

      // Out-of-bounds on y.
      if(boxNextPosition.y < 0 || boxNextPosition.y >= staticBoard.size()) //checking if box is leaving board's y
        return;  // TODO: maybe do something

      // Out-of-bounds on x.
      if(boxNextPosition.x < 0 || boxNextPosition.x >= staticBoard[nextPosition.y].size()) //checking if box is leaving board's x
        return;  // TODO: maybe do something

      if(dynamicBoard[boxNextPosition.y][boxNextPosition.x].getType() == SokoObject::EMPTY &&
          staticBoard[boxNextPosition.y][boxNextPosition.x].getType() != SokoObject::WALL) {
        dynamicBoard[boxNextPosition.y][boxNextPosition.x] = SokoObject(SokoObject::LIGHT_BOX);
        dynamicBoard[nextPosition.y][nextPosition.x] = SokoObject(SokoObject::CHARACTER);
        dynamicBoard[characterPosition.y][characterPosition.x] = SokoObject(SokoObject::EMPTY);
        characterPosition = nextPosition;
        boxMoved = true;
        characterMoved = true;
      }
    } 
    
    // CASE: Heavy box movement
    else if(dynamicBoard[nextPosition.y][nextPosition.x].getType() == SokoObject::HEAVY_BOX && 
        unresolvedLightBoxes == 0) {
      SokoPosition boxNextPosition = nextPosition + direction;

      // Out-of-bounds on y.
      if(boxNextPosition.y < 0 || boxNextPosition.y >= staticBoard.size()) //checking if box is leaving board's y
        return;  // TODO: maybe do something

      // Out-of-bounds on x.
      if(boxNextPosition.x < 0 || boxNextPosition.x >= staticBoard[nextPosition.y].size()) //checking if box is leaving board's x
        return;  // TODO: maybe do something

      if(dynamicBoard[boxNextPosition.y][boxNextPosition.x].getType() == SokoObject::EMPTY &&
          staticBoard[boxNextPosition.y][boxNextPosition.x].getType() != SokoObject::WALL) {
        dynamicBoard[boxNextPosition.y][boxNextPosition.x] = SokoObject(SokoObject::HEAVY_BOX);
        dynamicBoard[nextPosition.y][nextPosition.x] = SokoObject(SokoObject::CHARACTER);
        dynamicBoard[characterPosition.y][characterPosition.x] = SokoObject(SokoObject::EMPTY);
        characterPosition = nextPosition;
        boxMoved = true;
        characterMoved = true;
      }
    }
  }

  if(boxMoved)
    updateUnresolvedBoxes();

  if(characterMoved)
    moves.push(Movement(direction, boxMoved));
}

void SokoBoard::undo() {
  if (!moves.empty()) {
    Movement last = moves.top();
    moves.pop();

    SokoPosition previousPosition = characterPosition - last.direction;
    dynamicBoard[previousPosition.y][previousPosition.x] = SokoObject(SokoObject::CHARACTER);
    SokoPosition nextPosition = characterPosition + last.direction;
    
    if (last.boxMoved) {
      SokoObject::Type type = dynamicBoard[nextPosition.y][nextPosition.x].getType();
      dynamicBoard[characterPosition.y][characterPosition.x] = SokoObject(type);
      dynamicBoard[nextPosition.y][nextPosition.x] = SokoObject(SokoObject::EMPTY);
    }
    else {
      dynamicBoard[characterPosition.y][characterPosition.x] = SokoObject(SokoObject::EMPTY);
    }

    characterPosition = previousPosition;
  }
}

std::string SokoBoard::toString() const {
  std::stringstream ss;
  ss<< "Dynamic Board: " << endl;
  for(auto line : dynamicBoard) {
    for(auto obj : line)
      ss << " " << obj.getType();
    ss << endl;
  }
  ss<< "Static Board: " << endl;
  for(auto line : staticBoard) {
    for(auto obj : line)
      ss << " " << obj.getType();
    ss << endl;
  }
  return ss.str();
}

std::ostream& operator<<(std::ostream& os, const SokoBoard& s) {
  os << s.toString();
  return os;
}

void SokoBoard::updateUnresolvedBoxes() {
  unresolvedLightBoxes = lightBoxes;
  unresolvedHeavyBoxes = heavyBoxes;
  /* Every test here is necessary (and done only when necessary).
     If you don't trust me, waste your time and please, increase the counter.
     Time wasted with these tests: 0.12 hours.
     */
  for(unsigned y = 0; y < staticBoard.size(); y++) {
    for(unsigned x = 0; x < staticBoard[y].size(); x++) {
      if(staticBoard[y][x].getType() == SokoObject::TARGET) {
        if (dynamicBoard[y][x].getType() == SokoObject::LIGHT_BOX) {
          unresolvedLightBoxes--;
        }
        if (dynamicBoard[y][x].getType() == SokoObject::HEAVY_BOX) {
          unresolvedHeavyBoxes--;
        }
      }
    }
  }
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

SokoObject SokoBoard::getDynamic(int x, int y) {
  return dynamicBoard[y][x];
}

SokoObject SokoBoard::getStatic(int x, int y) {
  return staticBoard[y][x];
}

unsigned SokoBoard::getNumberOfRows() const {
  return staticBoard.size();
}

unsigned SokoBoard::getNumberOfColumns() const {
  return staticBoard[0].size();
}

}
