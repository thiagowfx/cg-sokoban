#ifndef _MENU_H_
#define _MENU_H_

#include <vector>
#include "helpers.hpp"
#include "SDL_ttf.h"
using std::vector;

class Menu {
  public:
    Menu(SDL_Renderer *windowRenderer, const SDL_Color& labelInColor, const SDL_Color& labelOutColor, TTF_Font *labelFont, int screenWidth, int screenHeight, vector<const char*> labels, SDL_Texture* backgroundTexture = NULL);
    ~Menu();
    void renderMainMenu();
    int getCurrentIndex() const;
    void prevIndex();
    void nextIndex();

  private:
    vector<SDL_Texture*> inTextures;
    vector<SDL_Texture*> outTextures;
    vector<SDL_Rect> rects;
    int currentIndex = 0;

  private:
    SDL_Renderer *windowRenderer;
    SDL_Color labelInColor;
    SDL_Color labelOutColor;
    TTF_Font *labelFont;
    int screenWidth;
    int screenHeight;
    vector<const char*> labels;
    SDL_Texture* backgroundTexture;
};

#endif // _MENU_H_
