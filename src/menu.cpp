#include "menu.hpp"

Menu::Menu(SDL_Renderer *windowRenderer, const SDL_Color& labelInColor, const SDL_Color& labelOutColor, TTF_Font *labelFont, int screenWidth, int screenHeight, vector<const char*> labels) :
    windowRenderer(windowRenderer),
    labelInColor(labelInColor),
    labelOutColor(labelOutColor),
    labelFont(labelFont),
    screenWidth(screenWidth),
    screenHeight(screenHeight),
    labels(labels)
{
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

bool Menu::rectCollision(SDL_Rect rect1, SDL_Rect rect2) const {
    return(!(rect1.x + rect1.w <= rect2.x || rect1.x >= rect2.x + rect2.w || rect1.y + rect1.h <= rect2.y || rect1.y >= rect2.y + rect2.h));
}

void Menu::renderMainMenu() const {
    /* Get the mouse position. */
    SDL_Rect mouseRect;
    mouseRect.w = 0, mouseRect.h = 0;
    Uint32 mouseState = SDL_GetMouseState(&mouseRect.x, &mouseRect.y);

    /* Draw the labels on the renderer, with the correct colors. */
    SDL_RenderClear(windowRenderer);
    for (unsigned i = 0; i < labels.size(); ++i) {
        if (rectCollision(mouseRect, rects[i])) {
            SDL_RenderCopy(windowRenderer, inTextures[i], NULL, &rects[i]);
        }
        else {
            SDL_RenderCopy(windowRenderer, outTextures[i], NULL, &rects[i]);
        }
    }
    SDL_RenderPresent(windowRenderer);

    /* Test the click events. */
    // if(rectCollision(mouseRect, quitRect) && (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)))
    //     *context = QUIT;
    // else if(rectCollision(mouseRect, startRect) && (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)))
    //     *context = GAME;
}

void Menu::renderGameWon() const {
    SDL_Surface* surface = TTF_RenderText_Solid(labelFont, "Congratulations, you've won the game!", labelOutColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(windowRenderer, surface);
    SDL_Rect rect = {(screenWidth - std::min(surface->w, screenWidth))/2, (screenHeight - surface->h)/2, std::min(surface->w, screenWidth), surface->h};

    SDL_RenderClear(windowRenderer);
    SDL_RenderCopy(windowRenderer, texture, NULL, &rect);
    SDL_RenderPresent(windowRenderer);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
