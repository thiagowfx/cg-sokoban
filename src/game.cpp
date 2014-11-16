#include "game.hpp"

void sdldie(const char* msg) {
  std::cout << msg << std::endl;
  std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
  exit(1);
}

Game::Game(SDL_Window* window, SDL_GLContext* glContext, int screenWidth, int screenHeight) :
  window(window),
  glContext(glContext),
  screenWidth(screenWidth),
  screenHeight(screenHeight) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    /* Create the OpenGL context. */
    *glContext = SDL_GL_CreateContext(window);
    if(*glContext == NULL) {
      sdldie("OpenGL context could not be created");
    }

    /* Use VSync. */
    if(SDL_GL_SetSwapInterval(1) < 0) {
      sdldie("Warning: Unable to set VSync");
    }

    /* OpenGL initialization. */

    /* Z-Depth. */
    glEnable(GL_DEPTH_TEST);

    //Limpa a tela com a cor do parâmetro (boa prática de OpenGL)
    glClearColor(0.5, 0.5, 0.5, 1.0);

    //Seta a matriz de projeção na identidade
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Seta a pocição da câmera (posição da câmera, para onde ela está olhando e o vetor up)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(4.0, 4.0, 2.0, 0, 0, 0, 0, -0.1, 1); //camera na posição (2,-2,0), olhando para origem e up = (0,-0.1,1)

    sokoReshape();
  }

Game::~Game() {

}

void Game::renderScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  //Paredes Parte de cima
  drawCube(0.0, 0.0, 0.0, 0.5);
  drawCube(0.5, 0.0, 0.0, 0.5);
  drawCube(1.0, 0.0, 0.0, 0.5);
  drawCube(1.5, 0.0, 0.0, 0.5);
  drawCube(2.0, 0.0, 0.0, 0.5);
  drawCube(2.5, 0.0, 0.0, 0.5);

  //Paredes lateral direita
  drawCube(0.0, 0.5, 0.0, 0.5);
  drawCube(0.0, 1.0, 0.0, 0.5);
  drawCube(0.0, 1.5, 0.0, 0.5);
  drawCube(0.0, 2.0, 0.0, 0.5);
  drawCube(0.0, 2.5, 0.0, 0.5);
  drawCube(0.0, 3.0, 0.0, 0.5);
  drawCube(0.0, 3.5, 0.0, 0.5);
  drawCube(0.0, 4.0, 0.0, 0.5);

  //Paredes Parte de baixo
  drawCube(0.0, 4.0, 0.0, 0.5);
  drawCube(0.5, 4.0, 0.0, 0.5);
  drawCube(1.0, 4.0, 0.0, 0.5);
  drawCube(1.5, 4.0, 0.0, 0.5);
  drawCube(2.0, 4.0, 0.0, 0.5);
  drawCube(2.5, 4.0, 0.0, 0.5);

  //Paredes lateral direita
  drawCube(2.5, 0.5, 0.0, 0.5);
  drawCube(2.5, 1.0, 0.0, 0.5);
  drawCube(2.5, 1.5, 0.0, 0.5);
  drawCube(2.5, 2.0, 0.0, 0.5);
  drawCube(2.5, 2.5, 0.0, 0.5);
  drawCube(2.5, 3.0, 0.0, 0.5);
  drawCube(2.5, 3.5, 0.0, 0.5);
  drawCube(2.5, 4.0, 0.0, 0.5);

  glFlush();
  SDL_GL_SwapWindow(window);
}

void Game::drawCube(GLdouble x, GLdouble y, GLdouble z, GLdouble edge)
{
  /* Essa função desenha um cubo de tamanho edge x edge x edge na posição (x, y, z)
     É importante passar sempre o valor correto para os argumentos se não resultados estranhos são obtidos*/
  GLdouble halfEdge = edge/2;
  glEnable(GL_TEXTURE_2D);



  glPushMatrix();
  glTranslatef(x, y, z);

  glBegin(GL_POLYGON);
  glColor3f(1.0, 1.0, 0.0);

  glVertex3f(  halfEdge, -halfEdge, -halfEdge );
  glVertex3f(  halfEdge,  halfEdge, -halfEdge );
  glVertex3f( -halfEdge,  halfEdge, -halfEdge );
  glVertex3f( -halfEdge, -halfEdge, -halfEdge );
  glEnd();

  // White side
  glBegin(GL_POLYGON);
  glColor3f(1.0, 1.0, 1.0);

  glVertex3f(  halfEdge, -halfEdge, halfEdge );
  glVertex3f(  halfEdge,  halfEdge, halfEdge );
  glVertex3f( -halfEdge,  halfEdge, halfEdge );
  glVertex3f( -halfEdge, -halfEdge, halfEdge );
  glEnd();

  // Purple side
  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 1.0);

  glVertex3f( halfEdge, -halfEdge, -halfEdge );
  glVertex3f( halfEdge,  halfEdge, -halfEdge );
  glVertex3f( halfEdge,  halfEdge,  halfEdge );
  glVertex3f( halfEdge, -halfEdge,  halfEdge );
  glEnd();

  // Green side
  glBegin(GL_POLYGON);
  glColor3f(0.0, 1.0, 0.0);

  glVertex3f( -halfEdge, -halfEdge,  halfEdge );
  glVertex3f( -halfEdge,  halfEdge,  halfEdge );
  glVertex3f( -halfEdge,  halfEdge, -halfEdge );
  glVertex3f( -halfEdge, -halfEdge, -halfEdge );
  glEnd();

  // Blue side
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.0, 1.0);

  glVertex3f(  halfEdge,  halfEdge,  halfEdge );
  glVertex3f(  halfEdge,  halfEdge, -halfEdge );
  glVertex3f( -halfEdge,  halfEdge, -halfEdge );
  glVertex3f( -halfEdge,  halfEdge,  halfEdge ); 
  glEnd();

  // Red side
  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 0.0);

  glVertex3f(  halfEdge, -halfEdge, -halfEdge );
  glVertex3f(  halfEdge, -halfEdge,  halfEdge );
  glVertex3f( -halfEdge, -halfEdge,  halfEdge );
  glVertex3f( -halfEdge, -halfEdge, -halfEdge );
  glEnd();

  glPopMatrix();
}

void Game::setOldPosition(GLdouble x, GLdouble y) {
  this->oldx = x;
  this->oldy = y;
}

void Game::setNewPosition(GLdouble xnew, GLdouble ynew) {
  int passo_x = xnew - oldx;
  int passo_y = ynew - oldy;

  setOldPosition(xnew, ynew);

  glMatrixMode(GL_MODELVIEW);
  if(passo_x != 0) {
    glRotatef(atan(2*passo_x), 0, 0, 1);
  }
  if(passo_y != 0) {
    glRotatef(atan(2*passo_y), 0, 1, 0);
  }
  glFlush();
  SDL_GL_SwapWindow(window);
}

void Game::sokoReshape() {
  // TODO: atualizar screenWidth, screenHeight
  glViewport (0, 0, screenWidth, screenHeight);	//muda a Viewport para a janela toda
  //seta a projeção
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //gluOrtho2D(1.0, 0.0, 1.0, 0.0);
  gluPerspective(60.0, (GLdouble)screenWidth/(GLdouble)screenHeight, 1.0, 10.0) ; //atualiza o aspectratio para os novos valores
  glMatrixMode(GL_MODELVIEW);
}
