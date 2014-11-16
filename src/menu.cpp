#include "menu.hpp"

Menu::Menu(SDL_Renderer *windowRenderer, const SDL_Color& labelInColor, const SDL_Color& labelOutColor, TTF_Font *labelFont, int screenWidth, int screenHeight, vector<const char*> labels, SDL_Texture* backgroundTexture) :
  windowRenderer(windowRenderer),
  labelInColor(labelInColor),
  labelOutColor(labelOutColor),
  labelFont(labelFont),
  screenWidth(screenWidth),
  screenHeight(screenHeight),
  labels(labels),
  backgroundTexture(backgroundTexture) {
    for (unsigned i = 0; i < labels.size(); ++i) {
      SDL_Surface* inSurface = TTF_RenderText_Solid(labelFont, labels[i], labelInColor);
      SDL_Surface* outSurface = TTF_RenderText_Solid(labelFont, labels[i], labelOutColor);

      inTextures.push_back(SDL_CreateTextureFromSurface(windowRenderer, inSurface));
      outTextures.push_back(SDL_CreateTextureFromSurface(windowRenderer, outSurface));
      rects.push_back(SDL_Rect{(screenWidth - inSurface->w)/2, int((screenHeight - 1.5 * int(labels.size()) * inSurface->h)/2 + i * 1.5 * inSurface->h),inSurface->w, inSurface->h});

      SDL_FreeSurface(inSurface);
      SDL_FreeSurface(outSurface);
    }
  }

Menu::~Menu() {
  for (unsigned i = 0; i < labels.size(); ++i) {
    SDL_DestroyTexture(inTextures[i]);
    SDL_DestroyTexture(outTextures[i]);
  }
}

void Menu::renderMainMenu() {
  /* Get the mouse position. */
  SDL_Rect mouseRect{0, 0, 0, 0};
  SDL_GetMouseState(&mouseRect.x, &mouseRect.y);

  /* Draw the labels on the renderer, with the correct colors. */
  SDL_RenderClear(windowRenderer);
  if (backgroundTexture != NULL) {
    SDL_RenderCopy(windowRenderer, backgroundTexture, NULL, NULL);
  }
  bool collision = false;
  for (unsigned i = 0; i < labels.size(); ++i) {
    if (rectCollision(mouseRect, rects[i])) {
      SDL_RenderCopy(windowRenderer, inTextures[i], NULL, &rects[i]);
      currentIndex = i;
      collision = true;
    }
    else {
      SDL_RenderCopy(windowRenderer, outTextures[i], NULL, &rects[i]);
    }
  }
  if (!collision) {
    SDL_RenderCopy(windowRenderer, inTextures[currentIndex], NULL, &rects[currentIndex]);
  }
  SDL_RenderPresent(windowRenderer);
}

int Menu::getCurrentIndex() const {
  return currentIndex;
}

void Menu::prevIndex() {
  currentIndex = (currentIndex + labels.size() - 1) % labels.size();
}

void Menu::nextIndex() {
  currentIndex = (currentIndex + 1) % labels.size();
}

