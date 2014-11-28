#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <iostream>
#include <GL/glu.h>
#include <png.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef enum Context {
  CONTEXT_MAIN_MENU = 0,
  CONTEXT_GAME = 1,
  CONTEXT_GAME_WON = 2
} Context;

/// Log a message using SDL_LOG, then exit.
void LOG_SDL_DIE(const char*);

/// Return true if this is a movement key.
bool isMovementKey(const SDL_Keycode& key);

SDL_Texture* loadTexture(SDL_Renderer*, const char* path);
bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);

#endif // _HELPERS_H_
