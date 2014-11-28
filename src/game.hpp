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
#include <SOIL/SOIL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace Sokoban {
  class Game {
    public:
      Game(SDL_Window*, SDL_GLContext*, int screenWidth, int screenHeight);
      ~Game();

      /// Load the specified @level.
      void loadLevel(const unsigned level);

      /// Set the window size to @width x @height.
      void setWindowSize(unsigned width, unsigned height);

      void setOldPosition(GLdouble x, GLdouble y);
      void setNewPosition(GLdouble xnew, GLdouble ynew);

      /// Return true if the current level has been finished.
      bool isLevelFinished() const;

      /// Action of the move down key.
      bool moveDownAction();

      /// Action of the move up key.
      bool moveUpAction();

      /// Action of the move left key.
      bool moveLeftAction();

      /// Action of the move right key.
      bool moveRightAction();

      /// Undo action.
      void undoAction();

      /// Draws a cube of size edge centered at (x,y,z).
      void drawCube(GLdouble x, GLdouble y, GLdouble z, GLdouble edge, GLuint* textureIDs);

      /// Reshape function.
      void sokoReshape();

      /// Main function to render a scene.
      void renderScene();

      /// Render a single image, at the given path.
      void renderSingleImage(const char* path);

      /// Get the game board.
      SokoBoard* getGameBoard() const;

    private:
      /// Main SDL window.
      SDL_Window* window;

      /// The OpenGL context from SDL.
      SDL_GLContext* glContext;

      int screenWidth, screenHeight;

      /// The current soko board
      SokoBoard *board = NULL;

      GLdouble xold, yold;

      const char* targetPath[6] = {"assets/x.png", "assets/x.png", "assets/x.png", "assets/x.png", "assets/x.png", "assets/x.png"};
      GLuint textureTargetIDs[6];

      const char* characterPath[6] = {"assets/perrotta.jpg", "assets/perrotta.jpg", "assets/perrotta.jpg", "assets/perrotta.jpg", "assets/perrotta.jpg", "assets/perrotta.jpg"};
      GLuint textureCharacterIDs[6];

      const char* lightBoxPath[6] = {"assets/wood.png", "assets/wood.png", "assets/wood.png", "assets/wood.png", "assets/wood.png", "assets/wood.png"};
      GLuint textureLightBoxIDs[6];

      const char* heavyBoxPath[6] = {"assets/stone.png", "assets/stone.png", "assets/stone.png", "assets/stone.png", "assets/stone.png", "assets/stone.png"};
      GLuint textureHeavyBoxIDs[6];

      const char* wallPath[6] = {"assets/wall.png", "assets/wall.png", "assets/wall.png", "assets/wall.png", "assets/wall.png", "assets/wall.png"};
      GLuint textureWallIDs[6];

      const char* floorPath[6] = {"assets/wall.png", "assets/ftop.png", "assets/wall.png", "assets/wall.png", "assets/wall.png", "assets/wall.png"};
      GLuint textureFloorIDs[6];
  };
}

#endif // _GAME_H_
