#ifndef _MENU_H_
#define _MENU_H_

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
using std::vector;

bool rectCollision(SDL_Rect rect1, SDL_Rect rect2);

class Menu {
  public:
    Menu(SDL_Renderer *windowRenderer, const SDL_Color& labelInColor, const SDL_Color& labelOutColor, TTF_Font *labelFont, int screenWidth, int screenHeight, vector<const char*> labels);
    ~Menu();
    void renderMainMenu();
    int getCurrentIndex() const;
    void prevIndex();
    void nextIndex();
    SDL_Texture* loadTexture(const char* path) const;

  private:
    vector<SDL_Texture*> inTextures;
    vector<SDL_Texture*> outTextures;
    vector<SDL_Rect> rects;
    SDL_Texture* backgroundTexture;
    int currentIndex = 0;

  private:
    SDL_Renderer *windowRenderer;
    SDL_Color labelInColor;
    SDL_Color labelOutColor;
    TTF_Font *labelFont;
    int screenWidth;
    int screenHeight;
    vector<const char*> labels;
};

#endif // _MENU_H_
