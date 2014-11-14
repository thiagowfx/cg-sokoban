#ifndef _GUI_H_
#define _GUI_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class Gui {
public:
    Gui();
    ~Gui();
    void gameLoop();

private:
    SDL_Surface* loadSurfaceHelper(const std::string&);
    SDL_Texture* loadTextureHelper(const std::string&);

    void splashScreenPrelude();
    void loadMediaPrelude();

private:
    SDL_Window *window = NULL;
    SDL_Surface *windowSurface = NULL;
    SDL_Renderer *windowRenderer = NULL;
    SDL_Texture *splashTexture = NULL;
    TTF_Font *windowFont = NULL;

private:
    const unsigned SCREEN_WIDTH = 800;
    const unsigned SCREEN_HEIGHT = 600;
    const unsigned GAME_SPLASH_SCREEN_TIMEOUT = 1000;
    const char* GAME_TITLE = "Sokoban";
    const SDL_Color windowClearColor = {255, 165, 0, 255};
};

#endif // _GUI_H_
