#ifndef _GUI_H_
#define _GUI_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_image.h"

class Gui {
public:
    Gui();
    ~Gui();
    void gameLoop();

private:
    SDL_Surface* loadSurfaceHelper(std::string);
    SDL_Texture* loadTextureHelper(std::string);

    void splashScreenPrelude();
    void loadMediaPrelude();

private:
    SDL_Window *window = NULL;
    SDL_Surface *screenSurface = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *splashTexture = NULL;

private:
    const unsigned SCREEN_WIDTH = 800;
    const unsigned SCREEN_HEIGHT = 600;
    const unsigned GAME_SPLASH_SCREEN_TIMEOUT = 2000;
    const char* GAME_TITLE = "Sokoban";
};

#endif // _GUI_H_
