#ifndef _MENU_H_
#define _MENU_H_

#include "SDL.h"
#include "SDL_ttf.h"

class Menu {
public:
    Menu();
    Menu(SDL_Renderer *windowRenderer, const SDL_Color& labelInColor, const SDL_Color& labelOutColor, TTF_Font *labelFont, int screenWidth, int screenHeight);
    ~Menu();
    void firstMenu();
    bool rectCollision(SDL_Rect rect1, SDL_Rect rect2) const;

private:
    SDL_Texture *startInTexture;
    SDL_Texture *startOutTexture;
    SDL_Texture *quitInTexture;
    SDL_Texture *quitOutTexture;

    SDL_Rect startRect;
    SDL_Rect quitRect;

    SDL_Color labelInColor;
    SDL_Color labelOutColor;
    SDL_Renderer *windowRenderer;
};

#endif // _MENU_H_
