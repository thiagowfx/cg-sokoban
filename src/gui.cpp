#include "gui.hpp"

Gui::Gui() {
    /* Initialize SDL. */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        sdldie("SDL could not be initialized");
    }

    /* Set texture filtering to linear. */
    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    /* Create the main window. */
    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);// | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == NULL) {
        sdldie("SDL Window could not be created");
    }

    /* Create the renderer for the window. */
    windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    if(windowRenderer == NULL) {
        sdldie("Renderer could not be created");
    }

    /* Enable PNG and JPEG support from SDL2_image. */
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        sdldie("SDL_image could not initialize");
    }

    /* Enable TTF support from SDL2_TTF. */
    if(TTF_Init() == -1) {
        sdldie("SDL_ttf could not initialize");
    }
    else {
        windowFont = TTF_OpenFont("assets/Roboto-Regular.ttf", 60);
        if (windowFont == NULL) {
            sdldie("Failed to load the Roboto-Regular font");
        }
    }
}

Gui::~Gui() {
    /* Destroy OpenGL. */
    SDL_GL_DeleteContext(glContext);
    delete game;
    game = NULL;

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

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Gui::gameLoop() {
    bool quit = false;
    SDL_Event e;

    /* Show the game splash screen. */
    renderSplashScreen("assets/gopher.jpg", GAME_SPLASH_TIMEOUT);

    /* Show the main menu. */
    gameMenu = new Menu(windowRenderer, MENU_LABEL_IN_COLOR, MENU_LABEL_OUT_COLOR, windowFont, SCREEN_WIDTH, SCREEN_HEIGHT, vector<const char*>{"Level 1", "Level 2", "Level 3", "Quit"});

    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
                break;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                case SDLK_ESCAPE:
                case SDLK_q:
                    quit = true;
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    if (context == CONTEXT_MAIN_MENU) {
                        gameMenu->nextIndex();
                    }
                    break;
                case SDLK_w:
                case SDLK_UP:
                    if (context == CONTEXT_MAIN_MENU) {
                        gameMenu->prevIndex();
                    }
                    break;
                case SDLK_RETURN:
                    if (context == CONTEXT_MAIN_MENU) {
                        int index = gameMenu->getCurrentIndex();
                        if (index == 3) {
                            quit = true;
                            break;
                        }
                        else {
                            context = CONTEXT_GAME;
                        }
                    }
                    break;
                }
            }
	    else if (e.type == SDL_MOUSEMOTION) {
	      if (context == CONTEXT_GAME) {
		int xnew;
	        int ynew;
	        Uint32 mouseState = SDL_GetMouseState(&xnew, &ynew);
		if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		  game->setNewPosition(xnew, ynew);
		}
	      }
	    }
            else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
	        int x;
	        int y;
	        Uint32 mouseState = SDL_GetMouseState(&x, &y);
                if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                    SDL_Log("Mouse Button 1 (left) pressed.");
                    if (context == CONTEXT_MAIN_MENU) {
                        int index = gameMenu->getCurrentIndex();
                        if (index == 3) {
                            quit = true;
                            break;
                        }
                        else {
                            context = CONTEXT_GAME;
                        }
                    }
		    else if(context == CONTEXT_GAME) {
		      game->setOldPosition(x, y);		      
		    }
                }
            }
        }

        /* Actual rendering happens here. */
        if (context == CONTEXT_MAIN_MENU) {
            gameMenu->renderMainMenu();
        }
        else if (context == CONTEXT_GAME) {
            if(!OPENGL_LOADED) {
	      game = new Game(window, &glContext, SCREEN_WIDTH, SCREEN_HEIGHT);
                OPENGL_LOADED = true;
            }
            game->renderScene();
        }
        else if (context == CONTEXT_GAME_WON) {
            exit(0);
        }
        /* Actual rendering ends here. */
    }
}

SDL_Texture* Gui::loadTexture(const std::string& path) const {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL) {
        std::cout << "Unable to load image" << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        exit(1);
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(windowRenderer, loadedSurface);
        if(newTexture == NULL) {
            std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
            exit(1);
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void Gui::renderSplashScreen(const char* path, unsigned timeout) const {
    SDL_Texture* splashTexture = loadTexture(path);
    SDL_SetRenderDrawColor(windowRenderer, WINDOW_CLEAR_COLOR.r, WINDOW_CLEAR_COLOR.r, WINDOW_CLEAR_COLOR.b, WINDOW_CLEAR_COLOR.a);
    SDL_RenderClear(windowRenderer);
    SDL_RenderCopy(windowRenderer, splashTexture, NULL, NULL);
    SDL_RenderPresent(windowRenderer);
    SDL_Delay(timeout);
    SDL_DestroyTexture(splashTexture);
}

void Gui::renderSingleText(const char* text, unsigned timeout, SDL_Color color) const {
    SDL_Surface* surface = TTF_RenderText_Solid(windowFont, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(windowRenderer, surface);
    SDL_Rect rect = {(SCREEN_WIDTH - std::min(surface->w, SCREEN_WIDTH))/2, (SCREEN_HEIGHT - surface->h)/2, std::min(surface->w, SCREEN_WIDTH), surface->h};

    SDL_SetRenderDrawColor(windowRenderer, WINDOW_CLEAR_COLOR.r, WINDOW_CLEAR_COLOR.r, WINDOW_CLEAR_COLOR.b, WINDOW_CLEAR_COLOR.a);
    SDL_RenderClear(windowRenderer);
    SDL_RenderCopy(windowRenderer, texture, NULL, &rect);
    SDL_RenderPresent(windowRenderer);
    SDL_Delay(timeout);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
