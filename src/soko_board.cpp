#include "soko_board.hpp"

namespace Sokoban {
SokoBoard::SokoBoard(const char* filename) {
  string line;
  ifstream mapFile(filename);

  if (mapFile.is_open()) {
    int x_now(0), y_now(0);

    /* Read line-by-line. */
    while (getline(mapFile,line)) {
      vector<SokoObject> staticObjLine;
      vector<SokoObject> dynamicObjLine;
      istringstream streamLine(line);

      /* Read a line. */
      while(!streamLine.eof()) {
        SokoObject staticObj;
        SokoObject dynamicObj;
        int i_type;

        streamLine >> i_type;
        SokoObject::Type type = SokoObject::Type(i_type);

        /* Update counters. */
        if (type == SokoObject::LIGHT_BOX || type == SokoObject::HEAVY_BOX) {
          ++boxes;
        }
        else if (type == SokoObject::TARGET) {
          ++targets;
        }

        /* Build both boards. */
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
      }

      staticBoard.push_back(staticObjLine);
      dynamicBoard.push_back(dynamicObjLine);        
    }
    unresolvedBoxes = boxes;
    mapFile.close();
  }
  else {
    die("Unable to open file");
  }
}

void SokoBoard::move(Direction direction) {
  SokoPosition nextPosition = characterPosition + direction;

  if(staticBoard[nextPosition.x][nextPosition.y].getType() == SokoObject::EMPTY) {

    /* Character movement only. */
    if(dynamicBoard[nextPosition.x][nextPosition.y].getType() == SokoObject::EMPTY) {
      dynamicBoard[nextPosition.x][nextPosition.y] = SokoObject(direction);
      dynamicBoard[characterPosition.x][characterPosition.y] = SokoObject(SokoObject::EMPTY);
      characterPosition = nextPosition;
    }

    else if(dynamicBoard[nextPosition.x][nextPosition.y].getType() == SokoObject::LIGHT_BOX) {
      SokoPosition boxNextPosition = nextPosition + direction;
      if(dynamicBoard[boxNextPosition.x][boxNextPosition.y].getType() == SokoObject::EMPTY &&
        staticBoard[boxNextPosition.x][boxNextPosition.y].getType() == SokoObject::EMPTY) {
          dynamicBoard[boxNextPosition.x][boxNextPosition.y] = SokoObject(SokoObject::LIGHT_BOX);
          dynamicBoard[nextPosition.x][nextPosition.y] = SokoObject(direction);
          dynamicBoard[characterPosition.x][characterPosition.y] = SokoObject(SokoObject::EMPTY);
          characterPosition = nextPosition;
      }
    }
  }
}

string SokoBoard::toString() const {
  stringstream ss;

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

ostream& operator<<(ostream& os, const SokoBoard& s) {
  os << s.toString();
  return os;
}

unsigned SokoBoard::getNumberOfBoxes() const {
  return boxes;
}

unsigned SokoBoard::getNumberofTargets() const {
  return targets;
}

unsigned SokoBoard::getNumberOfUnresolvedBoxes() const {
  return unresolvedBoxes;
}

}
