#include "game.hpp"

void sdldie(const char* msg) {
    std::cout << msg << std::endl;
    std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
    exit(1);
}

Game::Game(SDL_Window* window, SDL_GLContext* glContext) :
    window(window),
    glContext(glContext) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    /* Create the OpenGL context. */
    *glContext = SDL_GL_CreateContext(window);
    if(*glContext == NULL) {
        sdldie("OpenGL context could not be created");
    }

    /* Use VSync. */
    if(SDL_GL_SetSwapInterval(1) < 0) {
        sdldie("Warning: Unable to set VSync");
    }
}

Game::~Game() {

}

void Game::renderScene() const {
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin( GL_QUADS );
    glColor3f(0, 1, 0);
    glVertex2f( -0.5f, -0.5f );
    glVertex2f( 0.5f, -0.5f );
    glVertex2f( 0.5f, 0.5f );
    glVertex2f( -0.5f, 0.5f );
    glEnd();
    SDL_GL_SwapWindow(window);
}
