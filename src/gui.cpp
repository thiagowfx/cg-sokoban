#include "gui.hpp"

SDL_Texture* loadTexture(SDL_Renderer* windowRenderer, const char* path) {
  SDL_Texture* newTexture = NULL;
  SDL_Surface* loadedSurface = IMG_Load(path);
  if(loadedSurface == NULL) {
    std::cout << "Unable to load image" << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
  else {
    newTexture = SDL_CreateTextureFromSurface(windowRenderer, loadedSurface);
    if(newTexture == NULL) {
      std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
      exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(loadedSurface);
  }
  return newTexture;
}

void renderSplashScreen(const char* path, unsigned timeout, SDL_Renderer* windowRenderer, SDL_Color backgroundColor) {
  SDL_Texture* splashTexture = loadTexture(windowRenderer, path);
  SDL_SetRenderDrawColor(windowRenderer, backgroundColor.r, backgroundColor.r, backgroundColor.b, backgroundColor.a);
  SDL_RenderClear(windowRenderer);
  SDL_RenderCopy(windowRenderer, splashTexture, NULL, NULL);
  SDL_RenderPresent(windowRenderer);
  SDL_Delay(timeout);
  SDL_DestroyTexture(splashTexture);
}

bool isMovementKey(const SDL_Keycode& key) {
  return key == SDLK_DOWN || key == SDLK_UP || key == SDLK_LEFT || key == SDLK_RIGHT ||
    key == SDLK_s || key == SDLK_w || key == SDLK_a || key == SDLK_d;
}

void SDL_DIE(std::string msg) {
  std::cout << msg << std::endl;
  std::cout << "DIE: SDL_Error: " << SDL_GetError() << std::endl;
  exit(EXIT_FAILURE);
}

namespace Sokoban {
  Gui::Gui() {
    /* Initialize SDL. */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
      SDL_DIE("SDL could not be initialized");
    }

    /* Set texture filtering to linear. */
    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      std::cout << "INFO: Warning: Linear texture filtering not enabled!" << std::endl;
    }

    /* Create the main window. */
    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);// | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == NULL) {
      SDL_DIE("SDL Window could not be created");
    }

    /* Create the renderer for the window. */
    windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    if(windowRenderer == NULL) {
      SDL_DIE("Renderer could not be created");
    }

    /* Enable PNG and JPEG support from SDL2_image. */
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
      SDL_DIE("SDL_image could not initialize");
    }

    /* Enable TTF support from SDL2_TTF. */
    if(TTF_Init() == -1) {
      SDL_DIE("SDL_ttf could not initialize");
    }
    else {
      windowFont = TTF_OpenFont(GAME_FONT_PATH, 60);
      if (windowFont == NULL) {
        SDL_DIE("Failed to load the font");
      }
    }

    /* Enable sound. */
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
      SDL_DIE("SDL_Mixer could not initialize");
    }
    else {
      soundBackgroundMusic = Mix_LoadMUS("assets/sound/expshooter2.mp3" );
      if(soundBackgroundMusic == NULL) {
        SDL_DIE("Failed to load background music");
      }

      soundCharacterMoved = Mix_LoadWAV("assets/sound/baseball_hit.wav");
      if(soundCharacterMoved == NULL) {
        SDL_DIE("Failed to load character movement sound");
      }

      soundBoxMoved = Mix_LoadWAV("assets/sound/blip.wav");
      if(soundBoxMoved == NULL) {
        SDL_DIE("Failed to load box movemend sound");
      }

      soundStageFinished = Mix_LoadWAV("assets/sound/stageFinished.wav");
      if (soundStageFinished == NULL) {
        SDL_DIE("Failed to load stage finished sound");
      }

      soundSplash = Mix_LoadWAV("assets/sound/pacman.wav");
      if (soundSplash == NULL) {
        SDL_DIE("Failed to load splash sound");
      }
    }
  }

  Gui::~Gui() {
    /* Destroy OpenGL. */
    SDL_GL_DeleteContext(glContext);
    delete game;
    game = NULL;

    /* Destroy textures. */
    SDL_DestroyTexture(backgroundTexture);
    backgroundTexture = NULL;

    /* Destroy the menu. */
    delete gameMenu;
    gameMenu = NULL;

    /* Destroy fonts. */
    TTF_CloseFont(windowFont);
    windowFont = NULL;

    /* Destroy renderer and window. */
    SDL_DestroyRenderer(windowRenderer);
    SDL_DestroyWindow(window);
    windowRenderer = NULL;
    window = NULL;

    /* Destroy sounds. */
    Mix_FreeMusic(soundBackgroundMusic);
    soundBackgroundMusic = NULL;

    Mix_FreeChunk(soundCharacterMoved);
    soundCharacterMoved = NULL;

    Mix_FreeChunk(soundBoxMoved);
    soundBoxMoved = NULL;

    Mix_FreeChunk(soundStageFinished);
    soundStageFinished = NULL;

    Mix_FreeChunk(soundSplash);
    soundSplash = NULL;

    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
  }

  void Gui::loadOpenGL() {
    /* Create the OpenGL context. */
    glContext = SDL_GL_CreateContext(window);
    if(glContext == NULL) {
      SDL_DIE("OpenGL context could not be created");
    }

    OPENGL_LOADED = true;
  }

  void Gui::gameLoop() {
    bool quit = false;
    SDL_Event e;

    /* Show the game splash screen. */
    // TODO: reenable this later.
    //Mix_PlayChannel(-1, soundSplash, 0);
    //renderSplashScreen(SPLASH_TEXTURE_PATH, GAME_SPLASH_TIMEOUT, windowRenderer, WINDOW_CLEAR_COLOR);

    /* Show the main menu. */
    backgroundTexture = loadTexture(windowRenderer, MENU_BACKGROUND_TEXTURE_PATH);
    gameMenu = new Menu(windowRenderer, MENU_LABEL_IN_COLOR, MENU_LABEL_OUT_COLOR, windowFont, SCREEN_WIDTH, SCREEN_HEIGHT, GAME_MENU_LABELS, backgroundTexture);

    /* Play the background music. */
    Mix_PlayMusic(soundBackgroundMusic, -1);

    while(!quit) {
      while(SDL_PollEvent(&e) != 0) {
        // Quit event.
        if (e.type == SDL_QUIT) {
          SDL_Log("SDL_QUIT event");
          quit = true; break;
        }

        // Window resize event.
        else if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED && context == CONTEXT_GAME) {
          unsigned width = e.window.data1;
          unsigned height = e.window.data2;
          SDL_Log("SDL_WINDOWEVENT: SDL_WINDOWEVENT_RESIZED: %d x %d", width, height);
          SDL_SetWindowSize(window, width, height);
          game->setWindowSize(width, height);
        }

        // Key press event.
        else if (e.type == SDL_KEYDOWN) {
          SDL_Log("SDL_KEYDOWN event: %s", SDL_GetKeyName(e.key.keysym.sym));

          switch(e.key.keysym.sym) {
            // Quit from the game.
            case SDLK_ESCAPE:
            case SDLK_q:
              quit = true; break;
              // Down key.
            case SDLK_s:
            case SDLK_DOWN:
              if (context == CONTEXT_MAIN_MENU) {
                gameMenu->nextIndex();
              }
              else if (context == CONTEXT_GAME){
                bool boxMoved = game->moveDownAction();
                if (boxMoved)
                  boxMovedEvent();
                else 
                  characterMovedEvent();
                SDL_Log(game->getGameBoard()->toString().c_str());
              }
              break;
              // Up key:
            case SDLK_w:
            case SDLK_UP:
              if (context == CONTEXT_MAIN_MENU) {
                gameMenu->prevIndex();
              }
              else if (context == CONTEXT_GAME){
                bool boxMoved = game->moveUpAction();
                if (boxMoved)
                  boxMovedEvent();
                else 
                  characterMovedEvent();
                SDL_Log(game->getGameBoard()->toString().c_str());
              }
              break;
              // Left key.
            case SDLK_a:
            case SDLK_LEFT:
              if (context == CONTEXT_GAME){
                bool boxMoved = game->moveLeftAction();
                if (boxMoved)
                  boxMovedEvent();
                else 
                  characterMovedEvent();
                SDL_Log(game->getGameBoard()->toString().c_str());
              }
              break;
              // Right key.
            case SDLK_d:
            case SDLK_RIGHT:
              if (context == CONTEXT_GAME){
                bool boxMoved = game->moveRightAction();
                if (boxMoved)
                  boxMovedEvent();
                else 
                  characterMovedEvent();
                SDL_Log(game->getGameBoard()->toString().c_str());
              }
              break;
              // Mute key
            case SDLK_m:
              if(Mix_PausedMusic() == true) {
                Mix_ResumeMusic();
                SDL_Log("Background music playing again");
              }
              else {
                Mix_PauseMusic();
                SDL_Log("Background music paused");
              }
              break;
              // Restart key
            case SDLK_r:
              if (context == CONTEXT_GAME) {
                SDL_Log("Level restarted");
                game->loadLevel(currentLevel);
              }
              break;
            case SDLK_u:
              if (context == CONTEXT_GAME) {
                bool boxMoved = game->undoAction();
                if (boxMoved)
                  boxMovedEvent();
                else
                  characterMovedEvent();
                SDL_Log("Undo action");
                SDL_Log(game->getGameBoard()->toString().c_str());
              }
              break;
            case SDLK_RETURN:
              if (context == CONTEXT_MAIN_MENU) {
                unsigned index = gameMenu->getCurrentIndex();
                if (index == GAME_MENU_LABELS.size() - 1) {
                  quit = true; break;
                }
                else {
                  context = CONTEXT_GAME;
                  if(!OPENGL_LOADED) {
                    loadOpenGL();
                    game = new Game(window, &glContext, SCREEN_WIDTH, SCREEN_HEIGHT, windowFont, windowRenderer);
                  }
                  game->loadLevel(currentLevel = index + 1);
                }
              }
              break;
          }
        }
        /// Mouse motion event.
        else if (e.type == SDL_MOUSEMOTION) {
          if (context == CONTEXT_GAME) {
            int x, y; Uint32 mouseState = SDL_GetMouseState(&x, &y);
            if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
              SDL_Log("Mouse Button 1 (left) is being pressed and moved: %d, %d", x, y);
              game->setNewPosition(x, y);
            }
          }
        }
        /// Mouse click event.
        else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
          int x, y; Uint32 mouseState = SDL_GetMouseState(&x, &y);
          if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            SDL_Log("Mouse Button 1 (left) pressed: %d, %d", x, y);
            if (context == CONTEXT_MAIN_MENU) {
              unsigned index = gameMenu->getCurrentIndex();
              if (index == GAME_MENU_LABELS.size() - 1) {
                quit = true; break;
              }
              else {
                context = CONTEXT_GAME;
                if(!OPENGL_LOADED) {
                  loadOpenGL();
                  game = new Game(window, &glContext, SCREEN_WIDTH, SCREEN_HEIGHT, windowFont, windowRenderer);
                }
                game->loadLevel(currentLevel = index + 1);
              }
            }
            else if(context == CONTEXT_GAME) {
              game->setOldPosition(x, y);
            }
          }
        }
      }

      // Actual rendering happens here.
      if (context == CONTEXT_MAIN_MENU) {
        gameMenu->renderMainMenu();
      }
      else if (context == CONTEXT_GAME) {
        game->renderScene();
        checkLoadNextLevel(e);
      }
      else if (context == CONTEXT_GAME_FINISHED) {
        SDL_Log("Congratulations, you've won the game!");
        game->renderSingleImage(GAME_FINISHED_IMAGE_PATH);
        Mix_HaltMusic(); 
        SDL_Delay(GAME_FINISHED_TIMEOUT);
        quit = true; break;
      }
      // Actual rendering ends here.
    }
  }

  void Gui::checkLoadNextLevel(const SDL_Event& e) {
    if (context == CONTEXT_GAME && isMovementKey(e.key.keysym.sym) && game->isLevelFinished()) {
      if (currentLevel == (GAME_MENU_LABELS.size() - 1)) {
        SDL_Log("Finished the last level (%d). Switching to CONTEXT_GAME_FINISHED.", currentLevel);
        context = CONTEXT_GAME_FINISHED;
      }
      else {
        SDL_Log("Finished level %d", currentLevel);
        game->loadLevel(++currentLevel);
      }
      Mix_PlayChannel(-1, soundStageFinished, 0);
      SDL_Delay(STAGE_FINISHED_TIMEOUT);
    }
  }

  void Gui::boxMovedEvent() const {
    Mix_PlayChannel(-1, soundBoxMoved, 0);
  }

  void Gui::characterMovedEvent() const {
    Mix_PlayChannel(-1, soundCharacterMoved, 0);
  }
}
