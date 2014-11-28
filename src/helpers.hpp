#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <iostream>
#include <GL/glu.h>
#include <png.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/// Log a message using SDL_LOG, then exit.
void LOG_SDL_DIE(const char*);

bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);

#endif // _HELPERS_H_
