#ifndef _GUI_H_
#define _GUI_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include "menu.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

typedef enum Context {
    FIRSTMENU,
    GAME
} Context;

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
    Menu gameMenu;

private:
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const int GAME_SPLASH_SCREEN_TIMEOUT = 1000;
    const char* GAME_TITLE = "Sokoban";
    const SDL_Color WINDOW_CLEAR_COLOR = {200, 200, 200, 255};
    const SDL_Color MENU_LABEL_IN_COLOR = {90, 90, 90, 255};
    const SDL_Color MENU_LABEL_OUT_COLOR = {255, 10, 10, 255};
};

#endif // _GUI_H_
