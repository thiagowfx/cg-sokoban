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

    void loadLevel(const unsigned level);
    void setWindowSize(unsigned width, unsigned height);
    void setOldPosition(GLdouble x, GLdouble y);
    void setNewPosition(GLdouble xnew, GLdouble ynew);
    bool isLevelFinished() const;

    void moveDownAction();
    void moveUpAction();
    void moveLeftAction();
    void moveRightAction();
    void undoAction();
    void restartAction();

    /* Draws a cube of size edge centered at position (x, y, z). */
    void drawCube(GLdouble x, GLdouble y, GLdouble z, GLdouble edge);
    void sokoReshape();
    void renderScene();
    void renderGameFinished();

  private:
    SDL_Window* window;
    SDL_GLContext* glContext;
    int screenWidth, screenHeight;
    SokoBoard *board = NULL;
    GLdouble xold, yold;

    const char* GAME_WON_IMAGE="assets/the_end.png";
};

#endif // _GAME_H_
