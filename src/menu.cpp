#include "menu.hpp"

Menu::Menu() {

}

Menu::Menu(SDL_Renderer *windowRenderer, const SDL_Color& labelInColor, const SDL_Color& labelOutColor, TTF_Font *labelFont, int screenWidth, int screenHeight) :
    windowRenderer(windowRenderer),
    labelInColor(labelInColor),
    labelOutColor(labelOutColor)
{
    /* Make the labels. */
    SDL_Surface* startInSurface = TTF_RenderText_Solid(labelFont, "Start", labelInColor);
    SDL_Surface* startOutSurface = TTF_RenderText_Solid(labelFont, "Start", labelOutColor);
    SDL_Surface* quitInSurface = TTF_RenderText_Solid(labelFont, "Quit", labelInColor);
    SDL_Surface* quitOutSurface = TTF_RenderText_Solid(labelFont, "Quit", labelOutColor);

    startInTexture = SDL_CreateTextureFromSurface(windowRenderer, startInSurface);
    startOutTexture = SDL_CreateTextureFromSurface(windowRenderer, startOutSurface);
    quitInTexture = SDL_CreateTextureFromSurface(windowRenderer, quitInSurface);
    quitOutTexture = SDL_CreateTextureFromSurface(windowRenderer, quitOutSurface);

    /* Make the rect of the labels. */
    startRect = {(screenWidth - startInSurface->w)/2, (screenHeight - 3 * startInSurface->h)/2, startInSurface->w, startInSurface->h};
    quitRect = {(screenWidth - quitInSurface->w)/2, (screenHeight + quitInSurface->h)/2, quitInSurface->w, quitInSurface->h};

    /* Free the surfaces. */
    SDL_FreeSurface(startInSurface);
    SDL_FreeSurface(startOutSurface);
    SDL_FreeSurface(quitInSurface);
    SDL_FreeSurface(quitOutSurface);
}

Menu::~Menu() {
    SDL_DestroyTexture(startInTexture);
    SDL_DestroyTexture(startOutTexture);
    SDL_DestroyTexture(quitInTexture);
    SDL_DestroyTexture(quitOutTexture);
}

bool Menu::rectCollision(SDL_Rect rect1, SDL_Rect rect2) const {
    return(!(rect1.x + rect1.w <= rect2.x || rect1.x >= rect2.x + rect2.w ||
                rect1.y + rect1.h <= rect2.y || rect1.y >= rect2.y + rect2.h));
}

void Menu::firstMenu() {
    /* Get the mouse position */
    SDL_Rect mouseRect;
    mouseRect.w = 0;
    mouseRect.h = 0;
    Uint32 mouseState = SDL_GetMouseState(&mouseRect.x, &mouseRect.y);

    /* Update the color of the labels. */
    if (rectCollision(mouseRect, startRect)) {
        // TODO
    }
    else if (rectCollision(mouseRect, quitRect)) {
        // TODO
    }

    /* Draw the labels on the renderer. */
    SDL_RenderCopy(windowRenderer, quitOutTexture, NULL, &quitRect);
    SDL_RenderCopy(windowRenderer, startOutTexture, NULL, &startRect);

    /* Test the click events. */
    // if(rectCollision(mouseRect, quitRect) && (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)))
    //     *context = QUIT;
    // else if(rectCollision(mouseRect, startRect) && (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)))
    //     *context = GAME;
}
