#ifndef _MENU_H_
#define _MENU_H_

#include <SDL2/SDL_ttf.h>
#include <vector>
#include "helpers.hpp"

/**
 * A reusable menu for SDL.
 */
class Menu {
  public:
    /** Construct a new menu. */
    Menu(SDL_Renderer *windowRenderer, const SDL_Color& labelInColor, const SDL_Color& labelOutColor, TTF_Font *labelFont, int screenWidth, int screenHeight, std::vector<const char*> labels, SDL_Texture* backgroundTexture = NULL);
    ~Menu();
    
    void renderMainMenu();
    
    /// Get current selected menu entry.
    unsigned getCurrentIndex() const;

    /// Select the previous menu entry (wraps).
    void prevIndex();

    /// Select the next menu entry (wraps).
    void nextIndex();

  private:
    std::vector<SDL_Texture*> inTextures;
    std::vector<SDL_Texture*> outTextures;
    std::vector<SDL_Rect> rects;

    /// Current selected menu entry.
    int currentIndex = 0;

  private:
    SDL_Renderer *windowRenderer;

    /// Color of the current selected menu entry.
    SDL_Color labelInColor;

    /// Color of non-selected menu entries.
    SDL_Color labelOutColor;

    /// Menu font type (TTF).
    TTF_Font *labelFont;
    
    /// Width of the screen.
    int screenWidth;

    /// Height of the screen.
    int screenHeight;

    /// Strings of menu labels.
    std::vector<const char*> labels;

    /// Background texture of this menu.
    SDL_Texture* backgroundTexture;
};

#endif // _MENU_H_
