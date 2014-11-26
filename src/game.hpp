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
#include <SOIL/SOIL.h>
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

    /* Draws a cube of size edge centered at position (x, y, z). */
    void drawCube(GLdouble x, GLdouble y, GLdouble z, GLdouble edge, GLuint* textureIDs);
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

    const char* targetPath[6] = {"assets/bottom.png", "assets/top.png", "assets/face1.png", "assets/face2.png", "assets/face3.png", "assets/face4.png"};
    GLuint textureTargetIDs[6];

    const char* characterPath[6] = {"assets/bottom.png", "assets/top.png", "assets/face1.png", "assets/face2.png", "assets/face3.png", "assets/face4.png"};
    GLuint textureCharacterIDs[6];

    const char* lightBoxPath[6] = {"assets/bottom.png", "assets/top.png", "assets/face1.png", "assets/face2.png", "assets/face3.png", "assets/face4.png"};
    GLuint textureLightBoxIDs[6];

    const char* heavyBoxPath[6] = {"assets/bottom.png", "assets/top.png", "assets/face1.png", "assets/face2.png", "assets/face3.png", "assets/face4.png"};
    GLuint textureHeavyBoxIDs[6];

    const char* wallPath[6] = {"assets/bottom.png", "assets/top.png", "assets/face1.png", "assets/face2.png", "assets/face3.png", "assets/face4.png"};
    GLuint textureWallIDs[6];

    const char* floorPath[6] = {"assets/bottom.png", "assets/top.png", "assets/face1.png", "assets/face2.png", "assets/face3.png", "assets/face4.png"};
    GLuint textureFloorIDs[6];

};

#endif // _GAME_H_
