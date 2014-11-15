#ifndef _MENU_H_
#define _MENU_H_

#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"
using std::vector;

class Menu {
public:
    Menu(SDL_Renderer *windowRenderer, const SDL_Color& labelInColor, const SDL_Color& labelOutColor, TTF_Font *labelFont, int screenWidth, int screenHeight);
    ~Menu();
    void firstMenu();
    bool rectCollision(SDL_Rect rect1, SDL_Rect rect2) const;

private:
    const vector<const char*> labels = {"Level 1", "Level 2", "Level 3", "Quit"};
    vector<SDL_Texture*> inTextures;
    vector<SDL_Texture*> outTextures;
    vector<SDL_Rect> rects;

private:
    SDL_Renderer *windowRenderer;
    SDL_Color labelInColor;
    SDL_Color labelOutColor;
    TTF_Font *labelFont;
    int screenWidth;
    int screenHeight;
};

#endif // _MENU_H_
