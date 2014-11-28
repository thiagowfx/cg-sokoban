#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <iostream>
#include <GL/glu.h>
#include <png.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);

#endif // _HELPERS_H_
