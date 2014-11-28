#ifndef _GUI_H_
#define _GUI_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include "game.hpp"
#include "helpers.hpp"
#include "sdl_menu.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
using namespace Sokoban;

/**
  This class glues up the SDL interface with the game logic.
  */
class Gui {
  /// Represents the context where the game might be.
  typedef enum Context {
    CONTEXT_MAIN_MENU = 0,
    CONTEXT_GAME = 1,
    CONTEXT_GAME_WON = 2
  } Context;

  public:
  /// SDL initialization.
  Gui();

  /// Clean up SDL artifacts.
  ~Gui();

  /// Main game loop. Continuously monitors for user input and renderizes the game on the scree.
  void gameLoop();

  private:
  void renderSingleText(const char* text, unsigned timeout, SDL_Color color = {0, 0, 0, 255}) const;
  void renderSplashScreen(const char* path, unsigned timeout) const;

  private:
  /// The main SDL window.
  SDL_Window *window = NULL;

  /// The main SDL window renderer.
  SDL_Renderer *windowRenderer = NULL;

  /// Menu background texture.
  SDL_Texture *backgroundTexture = NULL;

  /// Type of the font (TTF).
  TTF_Font *windowFont = NULL;

  /// The game menu.
  Menu *gameMenu = NULL;

  /// The game renderization engine.
  Game *game = NULL;

  /// The current stage the user is on.
  unsigned currentLevel;

  /// OpenGL context for SDL.
  SDL_GLContext glContext;

  /// The current context the user is on.
  Context context = CONTEXT_MAIN_MENU;

  /// Indicate if OpenGL has already been initialized.
  bool OPENGL_LOADED = false;

  private:
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 600;
  const int GAME_SPLASH_TIMEOUT = 1200;
  const vector<const char*> GAME_MENU_LABELS = vector<const char*>{"Stage 1", "Stage 2", "Stage 3", "Quit"}; // Quit must be the last option.
  const char* GAME_TITLE = "sokoban";
  const char* MENU_BACKGROUND_TEXTURE_PATH = "assets/textures/menu_background.png";
  const char* SPLASH_TEXTURE_PATH = "assets/textures/splash.png";
  const char* GAME_FONT_PATH = "assets/Roboto-Regular.ttf";
  const SDL_Color WINDOW_CLEAR_COLOR = SDL_Color{225, 225, 225, 255};
  const SDL_Color MENU_LABEL_IN_COLOR = SDL_Color{160, 120, 60, 255};
  const SDL_Color MENU_LABEL_OUT_COLOR = SDL_Color{0, 0, 0, 255};
};

#endif // _GUI_H_
