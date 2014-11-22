#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <iostream>
#include <GL/glu.h>
#include <png.h>
#include "SDL.h"
#include "SDL_image.h"

typedef enum Context {
  CONTEXT_MAIN_MENU = 0,
  CONTEXT_GAME = 1,
  CONTEXT_GAME_WON = 2
} Context;

namespace Sokoban {
  typedef enum Direction {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
  } Direction;
}

void LOG_SDL_DIE(const char*);
bool isMovementKey(const SDL_Keycode& key);
bool rectCollision(const SDL_Rect rect1, const SDL_Rect rect2);
SDL_Texture* loadTexture(SDL_Renderer*, const char* path);
bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);

#endif // _HELPERS_H_
