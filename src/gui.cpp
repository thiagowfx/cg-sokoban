#include "gui.hpp"

Gui::Gui() {
    /* Initialize SDL. */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not be initialized. SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    /* Set texture filtering to linear. */
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
        std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    /* Create a window. */
    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cout << "SDL Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    else {
        screenSurface = SDL_GetWindowSurface(window);
    }

    /* Create renderer for the window. */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(renderer == NULL) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 0xCC, 0xCC, 0xCC, 0xFF);
    }

    /* Initialize PNG and JPEG loading from SDL2_image. */
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        exit(1);
    }

    splashScreenPrelude();
    loadMediaPrelude();
}

Gui::~Gui() {
    /* Destroy textures. */
    // SDL_DestroyTexture(myTexture);
    // myTexture = NULL;

    /* Destroy surfaces. */
    SDL_FreeSurface(screenSurface);
    screenSurface = NULL;

    /* Destroy renderer and window. */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;

    IMG_Quit();
    SDL_Quit();
}

void Gui::gameLoop() {
    bool quit = false;
    SDL_Event e;

    while(!quit) {
        while( SDL_PollEvent( &e ) != 0 ) {
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

        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
        // SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
        SDL_UpdateWindowSurface(window);

        // SDL_RenderClear(renderer);
        // SDL_RenderCopy(renderer, splashTexture, NULL, NULL);
        // SDL_RenderPresent(renderer);
    }
}

SDL_Surface* Gui::loadSurfaceHelper(std::string path) {
    /* Load image at specified path. */
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL ) {
        std::cout << "Unable to load image " << path << "! SDL Error: " << SDL_GetError() << std::endl;
    }
    return loadedSurface;
}

SDL_Texture* Gui::loadTextureHelper(std::string path) {
    /* The final texture. */
    SDL_Texture* newTexture = NULL;

    /* Load image at specified path. */
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL) {
        std::cout << "Unable to load image" << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else {
        /* Create texture from surface pixels. */
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == NULL) {
            std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        /* Get rid of old loaded surface. */
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void Gui::splashScreenPrelude() {
    splashTexture = loadTextureHelper("assets/gopher.jpeg");
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, splashTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(GAME_SPLASH_SCREEN_TIMEOUT);
    SDL_DestroyTexture(splashTexture);
    splashTexture = NULL;
}

void Gui::loadMediaPrelude() {
    // myTexture = loadTextureHelper("assets/...");
}
