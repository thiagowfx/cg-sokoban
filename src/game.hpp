#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <GL/glu.h>
#include "SDL.h"
#include "SDL_opengl.h"

void sdldie(const char*);

class Game {
public:
    Game(SDL_Window*, SDL_GLContext*);
    ~Game();
    void renderScene() const;

private:
    SDL_Window* window;
    SDL_GLContext* glContext;
};

#endif // _GAME_H_
