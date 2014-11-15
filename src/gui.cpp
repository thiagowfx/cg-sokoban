#include "gui.hpp"

Gui::Gui() {
    /* Initialize SDL. */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not be initialized. SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    /* Set texture filtering to linear. */
    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    /* Create the main window. */
    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);// | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == NULL) {
        std::cout << "SDL Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    /* Create the renderer for the window. */
    windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    if(windowRenderer == NULL) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    /* Enable PNG and JPEG support from SDL2_image. */
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        exit(1);
    }

    /* Enable TTF support from SDL2_TTF. */
    if(TTF_Init() == -1) {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        exit(1);
    }
    else {
        windowFont = TTF_OpenFont("assets/Roboto-Regular.ttf", 60);
        if (windowFont == NULL) {
            std::cout << "Failed to load Roboto-Regular font! SDL_ttf error: " << TTF_GetError() << std::endl;
            exit(1);
        }
    }
}

Gui::~Gui() {
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
    context = CONTEXT_MAIN_MENU;
    gameMenu = new Menu(windowRenderer, MENU_LABEL_IN_COLOR, MENU_LABEL_OUT_COLOR, windowFont, SCREEN_WIDTH, SCREEN_HEIGHT, vector<const char*>{"Level 1", "Level 2", "Level 3", "Quit"});

    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                case SDLK_q:
                    quit = true;
                    break;
                }
            }
        }

        /* Actual rendering happens here. */
        if (context == CONTEXT_MAIN_MENU) {
            gameMenu->renderMainMenu();
        }
        else if (context == CONTEXT_GAME) {
            // TODO: draw the game here.
        }
        else if (context == CONTEXT_GAME_WON) {
            renderSingleText("Congratulations, you've won the game!", GAME_SPLASH_TIMEOUT);
            exit(0);
        }
        else if(context == CONTEXT_BLANK) {
            SDL_SetRenderDrawColor(windowRenderer, WINDOW_CLEAR_COLOR.r, WINDOW_CLEAR_COLOR.r, WINDOW_CLEAR_COLOR.b, WINDOW_CLEAR_COLOR.a);
            SDL_RenderClear(windowRenderer);
            SDL_RenderPresent(windowRenderer);
        }
        /* Actual rendering ends here. */
    }
}

SDL_Surface* Gui::loadSurface(const std::string& path) const {
    /* Load image at specified path. */
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == NULL) {
        std::cout << "Unable to load image " << path << "! SDL Error: " << SDL_GetError() << std::endl;
    }
    return loadedSurface;
}

SDL_Texture* Gui::loadTexture(const std::string& path) const {
    /* The final texture. */
    SDL_Texture* newTexture = NULL;

    /* Load image at specified path. */
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL) {
        std::cout << "Unable to load image" << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else {
        /* Create texture from surface pixels. */
        newTexture = SDL_CreateTextureFromSurface(windowRenderer, loadedSurface);
        if(newTexture == NULL) {
            std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        /* Get rid of old loaded surface. */
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
