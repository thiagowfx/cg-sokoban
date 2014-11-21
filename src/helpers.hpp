#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <iostream>
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

void die(const char*);
void sdldie(const char*);
bool rectCollision(const SDL_Rect rect1, const SDL_Rect rect2);
SDL_Texture* loadTexture(SDL_Renderer*, const char* path);

#endif // _HELPERS_H_
