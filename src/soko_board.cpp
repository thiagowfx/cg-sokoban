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
        if (type == SokoObject::HEAVY_BOX)
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

/**
TEMP:  
  stack < ??? > undoTree;
  Precisa guardar o que foi movido, e pra onde. 
  O personagem sempre vai ser guardado.
  Pior caso: guardar um personagem *e* uma caixa.

  Criar:
  void undo();

  ifs e elses, lembrar:
  - undo
  - unresolvedBoxesNumber (caso tenha movido para dentro ou para fora de um target
  - manipular todos os movimentos possiveis (caixa-caixa, caixa-parede, caixa-vazio, vazio, etc)
  - se mover alguma caixa, tomar cuidado para texturas: leve e pesada.
*/
void SokoBoard::move(Direction direction) {
  bool boxMoved = false;
  SokoPosition nextPosition = characterPosition + direction;
  if(nextPosition.y >= staticBoard.size()) //checking if it is leaving the board y
    return;  // TODO: maybe do something
  if(nextPosition.x >= staticBoard[nextPosition.y].size()) //checking if it is leaving the board x
    return;  // TODO: maybe do something
  if(staticBoard[nextPosition.y][nextPosition.x].getType() == SokoObject::EMPTY) {
    // Character movement only
    if(dynamicBoard[nextPosition.y][nextPosition.x].getType() == SokoObject::EMPTY) {
      dynamicBoard[nextPosition.y][nextPosition.x] = SokoObject(direction);
      dynamicBoard[characterPosition.y][characterPosition.x] = SokoObject(SokoObject::EMPTY);
      characterPosition = nextPosition;
    } else if(dynamicBoard[nextPosition.y][nextPosition.x].getType() 
      == SokoObject::LIGHT_BOX) { 
      // Light box also moving
      SokoPosition boxNextPosition = nextPosition + direction;
        if(boxNextPosition.y >= staticBoard.size()) //checking if box is leaving board's y
          return;  // TODO: maybe do something
        if(boxNextPosition.x >= staticBoard[nextPosition.y].size()) //checking if box is leaving board's x
          return;  // TODO: maybe do something
      if(dynamicBoard[boxNextPosition.y][boxNextPosition.x].getType() == SokoObject::EMPTY &&
        staticBoard[boxNextPosition.y][boxNextPosition.x].getType() == SokoObject::EMPTY) {
        dynamicBoard[boxNextPosition.y][boxNextPosition.x] = SokoObject(SokoObject::LIGHT_BOX);
        dynamicBoard[nextPosition.y][nextPosition.x] = SokoObject(direction);
        dynamicBoard[characterPosition.y][characterPosition.x] = SokoObject(SokoObject::EMPTY);
        characterPosition = nextPosition;
        boxMoved = true;
      }
    } else if(dynamicBoard[nextPosition.y][nextPosition.x].getType() 
      == SokoObject::HEAVY_BOX && unresolvedLightBoxes == 0) {
      // Heavy box also moving
      SokoPosition boxNextPosition = nextPosition + direction;
      if(boxNextPosition.y >= staticBoard.size()) //checking if box is leaving board's y
        return;  // TODO: maybe do something
      if(boxNextPosition.x >= staticBoard[nextPosition.y].size()) //checking if box is leaving board's x
        return;  // TODO: maybe do something
      if(dynamicBoard[boxNextPosition.y][boxNextPosition.x].getType() == SokoObject::EMPTY &&
        staticBoard[boxNextPosition.y][boxNextPosition.x].getType() == SokoObject::EMPTY) {
        dynamicBoard[boxNextPosition.y][boxNextPosition.x] = SokoObject(SokoObject::HEAVY_BOX);
        dynamicBoard[nextPosition.y][nextPosition.x] = SokoObject(direction);
        dynamicBoard[characterPosition.y][characterPosition.x] = SokoObject(SokoObject::EMPTY);
        characterPosition = nextPosition;
        boxMoved = true;
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

void SokoBoard::checkResolvedBoxes() {
  unresolvedLightBoxes = lightBoxes;
  unresolvedHeavyBoxes = heavyBoxes;
  /* Every test here is necessary (and done only when necessary).
   If you don't trust me, waste your time and please, increase the counter.
   Time wasted with these tests: 0.12 hours.
   */
  for(int y = 0; y < staticBoard.size(); y++) {
    for(int x = 0; x < staticBoard[y].size(); x++) {
      if(staticBoard[y][x].getType() == SokoObject::TARGET && 
        dynamicBoard[y][x].getType() == SokoObject::LIGHT_BOX)
        unresolvedLightBoxes--;
      else if(staticBoard[y][x].getType() == SokoObject::TARGET && 
        dynamicBoard[y][x].getType() == SokoObject::HEAVY_BOX)
        unresolvedHeavyBoxes--;
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
  return getNumberOfUnresolvedBoxes()  == 0;
}

SokoObject SokoBoard::getDynamic(int x, int y) {
  return dynamicBoard[y][x];
}

SokoObject SokoBoard::getStatic(int x, int y) {
  return staticBoard[y][x];
}

}
