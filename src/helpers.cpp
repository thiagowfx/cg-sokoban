#include "helpers.hpp"

void LOG_DIE(const char* msg) {
  std::cout << "DIE: " << msg << std::endl;
  exit(EXIT_FAILURE);
}

void LOG_INFO(const char* msg) {
  std::cout << "INFO: " << msg << std::endl;
}

void LOG_SDL_DIE(const char* msg) {
  std::cout << msg << std::endl;
  std::cout << "DIE: SDL_Error: " << SDL_GetError() << std::endl;
  exit(EXIT_FAILURE);
}

bool isMovementKey(const SDL_Keycode& key) {
  return key == SDLK_DOWN || key == SDLK_UP || key == SDLK_LEFT || key == SDLK_RIGHT ||
      key == SDLK_s || key == SDLK_w || key == SDLK_a || key == SDLK_d;
}

bool rectCollision(const SDL_Rect rect1, const SDL_Rect rect2) {
  return(!(rect1.x + rect1.w <= rect2.x || rect1.x >= rect2.x + rect2.w || rect1.y + rect1.h <= rect2.y || rect1.y >= rect2.y + rect2.h));
}

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
