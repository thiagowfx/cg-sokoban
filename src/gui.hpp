#ifndef _GUI_H_
#define _GUI_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include "game.hpp"
#include "sdl_menu.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

/// Load a SDL Texture with the given renderer at the given path.
SDL_Texture* loadTexture(SDL_Renderer*, const char* path);

/// Render a splash screen with the given timeout..
void renderSplashScreen(const char* path, unsigned timeout, SDL_Renderer*, SDL_Color);

/// Return true if @key is a movement key.
bool isMovementKey(const SDL_Keycode& key);

/// Log a message using SDL_LOG, then exit.
void SDL_DIE(std::string);

namespace Sokoban {
  /**
    This class glues up the SDL interface with the game logic.
    */
  class Gui {
    /// Represents the context where the game might be.
    typedef enum Context {
      CONTEXT_MAIN_MENU = 0,
      CONTEXT_GAME = 1,
      CONTEXT_GAME_FINISHED = 2
    } Context;

    public:
    /// SDL initialization.
    Gui();

    /// Clean up SDL artifacts.
    ~Gui();

    /// Main game loop. Continuously monitors for user input and renderizes the game on the scree.
    void gameLoop();

    private:
    /// Load OpenGL for the first time.
    void loadOpenGL();

    /// Check if the current level is finished. If yes, load the next level or end the game, if it is the last level.
    void checkLoadNextLevel(const SDL_Event&);

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

    // Game settings.
    
    /// Game background music.
    Mix_Music *soundBackgroundMusic = NULL;

    /// Sound played after moving the character.
    Mix_Chunk *soundCharacterMoved = NULL;

    /// The screen width.
    const int SCREEN_WIDTH = 800;

    /// The screen height.
    const int SCREEN_HEIGHT = 600;

    // Duration of the game splash screen (in milliseconds).
    const int GAME_SPLASH_TIMEOUT = 1000;

    /// Duration of the end game screen (in milliseconds).
    const int GAME_FINISHED_TIMEOUT = 3000;

    /// Delay between two stages.
    const int STAGE_FINISHED_TIMEOUT = 1500;

    const vector<const char*> GAME_MENU_LABELS = vector<const char*>{"Stage 1", "Stage 2", "Stage 3", "Quit"}; // Quit must be the last option.

    /// Name of the game.
    const char* GAME_TITLE = "SOKOLAN";

    /// Path for the menu background texture.
    const char* MENU_BACKGROUND_TEXTURE_PATH = "assets/textures/menu_background.png";

    /// Path for the splash screen texture.
    const char* SPLASH_TEXTURE_PATH = "assets/textures/splash.png";

    /// Path to the game font.
    const char* GAME_FONT_PATH = "assets/Roboto-Regular.ttf";

    /// Background color.
    const SDL_Color WINDOW_CLEAR_COLOR = SDL_Color{192, 192, 192, 255};

    /// Color of the currently selected menu entry.
    const SDL_Color MENU_LABEL_IN_COLOR = SDL_Color{160, 120, 60, 255};

    /// Color of non-selected menu entries.
    const SDL_Color MENU_LABEL_OUT_COLOR = SDL_Color{0, 0, 0, 255};
  };
}

#endif // _GUI_H_
