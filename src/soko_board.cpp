#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "stdafx.h"
#include "soko_board.h"
#include "soko_objects\soko_objects.h"

using namespace std;

namespace Sokoban {
SokoBoard::SokoBoard(std::string filename) {
  string line;
  ifstream mapFile ("map1.sok");
  istringstream streamLine;

  if (mapFile.is_open())
  {
    while ( getline (mapFile,line) )
    {
      vector<SokoObject> staticObjLine;
      vector<SokoObject> dynamicObjLine;
      while(! streamLine.eof()) {
        SokoObject staticObj;
        SokoObject dynamicObj;
        int i_type;
        streamLine >> i_type;
        SokoObject::Type type = (SokoObject::Type) i_type;
        if(type == SokoObject::EMPTY || type == SokoObject::TARGET || type == SokoObject::WALL) {
          staticObj = SokoObject(type);
          dynamicObj = SokoObject(SokoObject::EMPTY);
        } else {
          staticObj = SokoObject(SokoObject::EMPTY);
          dynamicObj = SokoObject(type);
        }
        staticObjLine.push_back(staticObj);
        dynamicObjLine.push_back(dynamicObj);
      }
      staticBoard.push_back(staticObjLine);
      dynamicBoard.push_back(dynamicObjLine);        
    }
    mapFile.close();
  }

  else cout << "Unable to open file"; 

}

string SokoBoard::toString() {
  stringstream ss;
  ss<< "Dynamic Board: " << endl;
  for(auto line : dynamicBoard) {
    for(auto obj : line)
      ss << " " << (int) obj.getType();
    ss << endl;
  }

  ss<< "Static Board: " << endl;
  for(auto line : staticBoard) {
    for(auto obj : line)
      ss << " " << (int) obj.getType();
    ss << endl;
  }
}

}  //Sokoban