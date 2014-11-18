#include "helpers.hpp"

void sdldie(const char* msg) {
  std::cout << msg << std::endl;
  std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
  exit(1);
}

bool rectCollision(const SDL_Rect rect1, const SDL_Rect rect2) {
  return(!(rect1.x + rect1.w <= rect2.x || rect1.x >= rect2.x + rect2.w || rect1.y + rect1.h <= rect2.y || rect1.y >= rect2.y + rect2.h));
}

SDL_Texture* loadTexture(SDL_Renderer* windowRenderer, const char* path) {
  SDL_Texture* newTexture = NULL;
  SDL_Surface* loadedSurface = IMG_Load(path);
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
