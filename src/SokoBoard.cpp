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
  ifstream myfile ("map1.sok");
  istringstream streamLine;

  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      //cout << line << '\n';
      vector<SokoObject> staticObjLine;
      vector<SokoObject> dynamicObjLine;
      while(! streamLine.eof()) {
        SokoObject* staticObj;
        SokoObject* dynamicObj;
        int i_type;
        streamLine >> i_type;
        switch((SokoObject::Type) i_type ) {
          case SokoObject::EMPTY:
            staticObj = (SokoObject*) & SokoEmpty();
            dynamicObj = (SokoObject*) & SokoEmpty();
          break;
          case SokoObject::CHARACTER:
            dynamicObj = (SokoObject*) & SokoCharacter();
            staticObj = (SokoObject*) & SokoEmpty();
          break;
          case SokoObject::LIGHT_BOX:
            dynamicObj = (SokoObject*) & SokoLightBox();
            staticObj = (SokoObject*) & SokoEmpty();
          break;
          case SokoObject::HEAVY_BOX:
            dynamicObj = (SokoObject*) & SokoHeavyBox();
            staticObj = (SokoObject*) & SokoEmpty();
          break;
          case SokoObject::WALL:
            staticObj = (SokoObject*) & SokoWall();
            dynamicObj = (SokoObject*) & SokoEmpty();
          break;
          case SokoObject::TARGET:
            staticObj = (SokoObject*) & SokoTarget();
            dynamicObj = (SokoObject*) & SokoEmpty();
          break;
          staticObjLine.push_back(*staticObj);
          dynamicObjLine.push_back(*dynamicObj);
        }
        
         staticBoard.push_back(staticObjLine);
         dynamicBoard.push_back(dynamicObjLine);
        
      }      
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 

  return 0;
}

}  //Sokoban