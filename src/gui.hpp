#ifndef _GUI_H_
#define _GUI_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include "game.hpp"
#include "menu.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

typedef enum Context {
    CONTEXT_MAIN_MENU,
    CONTEXT_GAME,
    CONTEXT_GAME_WON
} Context;

class Gui {
public:
    Gui();
    ~Gui();
    void gameLoop();

private:
    SDL_Texture* loadTexture(const std::string&) const;
    void renderSingleText(const char* text, unsigned timeout, SDL_Color color = {0, 0, 0, 255}) const;
    void renderSplashScreen(const char* path, unsigned timeout) const;

private:
    SDL_Window *window = NULL;
    SDL_Renderer *windowRenderer = NULL;
    TTF_Font *windowFont = NULL;
    Menu *gameMenu = NULL;
    Game *game = NULL;
    SDL_GLContext glContext;
    Context context = CONTEXT_MAIN_MENU;
    bool OPENGL_LOADED = false;

private:
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const int GAME_SPLASH_TIMEOUT = 500;
    const char* GAME_TITLE = "Sokoban";
    const SDL_Color WINDOW_CLEAR_COLOR = SDL_Color{225, 225, 225, 255};
    const SDL_Color MENU_LABEL_IN_COLOR = SDL_Color{110, 110, 110, 255};
    const SDL_Color MENU_LABEL_OUT_COLOR = SDL_Color{10, 10, 10, 255};
};

#endif // _GUI_H_
