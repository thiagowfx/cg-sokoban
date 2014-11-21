#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

typedef enum Context {
  CONTEXT_MAIN_MENU,
  CONTEXT_GAME,
  CONTEXT_GAME_WON
} Context;

void sdldie(const char*);
bool rectCollision(const SDL_Rect rect1, const SDL_Rect rect2);
SDL_Texture* loadTexture(SDL_Renderer*, const char* path);

#endif // _HELPERS_H_
