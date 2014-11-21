#ifndef _GUI_H_
#define _GUI_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include "game.hpp"
#include "helpers.hpp"
#include "menu.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class Gui {
public:
  Gui();
  ~Gui();
  void gameLoop();

private:
  void renderSingleText(const char* text, unsigned timeout, SDL_Color color = {0, 0, 0, 255}) const;
  void renderSplashScreen(const char* path, unsigned timeout) const;

private:
  SDL_Window *window = NULL;
  SDL_Renderer *windowRenderer = NULL;
  SDL_Texture *backgroundTexture = NULL;
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
  const vector<const char*> GAME_MENU_LABELS = vector<const char*>{"Stage 1", "Stage 2", "Stage 3", "Quit"};
  const char* GAME_TITLE = "sokoban";
  const char* MENU_BACKGROUND_TEXTURE_PATH = "assets/menu_background.png";
  const char* SPLASH_TEXTURE_PATH = "assets/gopher.jpg";
  const char* GAME_FONT_PATH = "assets/Roboto-Regular.ttf";
  const SDL_Color WINDOW_CLEAR_COLOR = SDL_Color{225, 225, 225, 255};
  const SDL_Color MENU_LABEL_IN_COLOR = SDL_Color{160, 120, 60, 255};
  const SDL_Color MENU_LABEL_OUT_COLOR = SDL_Color{0, 0, 0, 255};
};

#endif // _GUI_H_
