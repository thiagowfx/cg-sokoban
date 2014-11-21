#ifndef _GAME_H_
#define _GAME_H_

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glu.h>
#include <iostream>
#include "soko_board.hpp"
#include "helpers.hpp"
#include "SDL.h"
#include "SDL_opengl.h"
using namespace Sokoban;

class Game {
  public:
    Game(SDL_Window*, SDL_GLContext*, int screenWidth, int screenHeight);
    ~Game();
    void renderScene();
    void setOldPosition(GLdouble x, GLdouble y);
    void setNewPosition(GLdouble xnew, GLdouble ynew);
    void sokoReshape();

  private:
    void drawCube(GLdouble x, GLdouble y, GLdouble z, GLdouble edge);

  private:
    SDL_Window* window;
    SDL_GLContext* glContext;
    int screenWidth;
    int screenHeight;

    GLdouble oldx;
    GLdouble oldy;
};

#endif // _GAME_H_
