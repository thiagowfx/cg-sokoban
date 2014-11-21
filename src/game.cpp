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
    //if(SDL_GL_SetSwapInterval(1) < 0) {
    //  sdldie("Warning: Unable to set VSync");
    //}

    /* OpenGL initialization. */

    /* Z-Depth. */
    glEnable(GL_DEPTH_TEST);

    /*Lighting initializations*/
    glEnable(GL_NORMALIZE);         //Normalizes the normal vectors of every vertex (ie. size = 1)
    glShadeModel(GL_SMOOTH);        //Shadind model is smooth
    glEnable(GL_LIGHTING);          //Enables lighting

    /*Cleans the background and sets it to the RGB parameters*/
    glClearColor(0.5, 0.5, 0.5, 1.0);

    /*Sets the Projection Matrix at the Identity*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /*Defines the camera's properties: where it is, where it's looking at, the up vector*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(4.0, 4.0, 2.0, 0, 0, 0, 0, -0.1, 1); //camera's initial position at (4,4,2), looking at (0,0,0) and up = (0,-0.1,1)

    sokoReshape();
  }

Game::~Game() {

}

void Game::renderScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /*Ambient's lighting - eg. Light all around despite the light sources*/
  GLfloat ambientIntesity[4] = {1.5, 1.5, 1.5, 1.0};          //Ambient's light is white
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientIntesity);

  /*Light source number 0*/
  GLfloat light0Intensity[4] = {0, 0, 1.0, 1.0};               //Light0 is blue
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Intensity);           //For diffuse reflection
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0Intensity);          //For specular reflection
  GLfloat light0Position[4] = {0, 0, 1, 0};                    //Light0's position at z-axis infinity
  glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
  glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0);             //Attenuation
  glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0); 
  glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1);
  glEnable(GL_LIGHT0);

    /*Light source number 1*/
  GLfloat light1Intensity[4] = {1.0, 0, 0, 1.0};               //Light1 is red
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Intensity);           //For diffuse reflection
  glLightfv(GL_LIGHT1, GL_SPECULAR, light1Intensity);          //For specular reflection
  GLfloat light1Position[4] = {1, 0, 0, 0};                    //Light1's position at x-axis infinity
  glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
  glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0);             //Attenuation
  glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0); 
  glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.1);
  glEnable(GL_LIGHT1);


  /*Objects drawing*/
  glMatrixMode(GL_MODELVIEW);

  /*The way of drawing is going to change in the future. Thus, the following portuguese comments are going to dissapear*/
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
  /* This function draws a cube of size (edge x edge x edge) at position (x, y, z)*/
  GLdouble halfEdge = edge/2;
  glEnable(GL_TEXTURE_2D);



  glPushMatrix();
  glTranslatef(x, y, z);

  glBegin(GL_POLYGON);
  glColor3f(1.0, 1.0, 0.0);

  glNormal3f(0, 0, -1);  glVertex3f(  halfEdge, -halfEdge, -halfEdge );
  glNormal3f(0, 0, -1);  glVertex3f(  halfEdge,  halfEdge, -halfEdge );
  glNormal3f(0, 0, -1);  glVertex3f( -halfEdge,  halfEdge, -halfEdge );
  glNormal3f(0, 0, -1);  glVertex3f( -halfEdge, -halfEdge, -halfEdge );
  glEnd();

  // White side
  glBegin(GL_POLYGON);
  glColor3f(1.0, 1.0, 1.0);

  glNormal3f(0, 0, 1);  glVertex3f(  halfEdge, -halfEdge, halfEdge );
  glNormal3f(0, 0, 1);  glVertex3f(  halfEdge,  halfEdge, halfEdge );
  glNormal3f(0, 0, 1);  glVertex3f( -halfEdge,  halfEdge, halfEdge );
  glNormal3f(0, 0, 1);  glVertex3f( -halfEdge, -halfEdge, halfEdge );
  glEnd();

  // Purple side
  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 1.0);

  glNormal3f(1, 0, 0);  glVertex3f( halfEdge, -halfEdge, -halfEdge );
  glNormal3f(1, 0, 0);  glVertex3f( halfEdge,  halfEdge, -halfEdge );
  glNormal3f(1, 0, 0);  glVertex3f( halfEdge,  halfEdge,  halfEdge );
  glNormal3f(1, 0, 0);  glVertex3f( halfEdge, -halfEdge,  halfEdge );
  glEnd();

  // Green side
  glBegin(GL_POLYGON);
  glColor3f(0.0, 1.0, 0.0);

  glNormal3f(-1, 0, 0);  glVertex3f( -halfEdge, -halfEdge,  halfEdge );
  glNormal3f(-1, 0, 0);  glVertex3f( -halfEdge,  halfEdge,  halfEdge );
  glNormal3f(-1, 0, 0);  glVertex3f( -halfEdge,  halfEdge, -halfEdge );
  glNormal3f(-1, 0, 0);  glVertex3f( -halfEdge, -halfEdge, -halfEdge );
  glEnd();

  // Blue side
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.0, 1.0);

  glNormal3f(0, 1, 0);  glVertex3f(  halfEdge,  halfEdge,  halfEdge );
  glNormal3f(0, 1, 0);  glVertex3f(  halfEdge,  halfEdge, -halfEdge );
  glNormal3f(0, 1, 0);  glVertex3f( -halfEdge,  halfEdge, -halfEdge );
  glNormal3f(0, 1, 0);  glVertex3f( -halfEdge,  halfEdge,  halfEdge ); 
  glEnd();

  // Red side
  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 0.0);

  glNormal3f(0, -1, 0);  glVertex3f(  halfEdge, -halfEdge, -halfEdge );
  glNormal3f(0, -1, 0);  glVertex3f(  halfEdge, -halfEdge,  halfEdge );
  glNormal3f(0, -1, 0);  glVertex3f( -halfEdge, -halfEdge,  halfEdge );
  glNormal3f(0, -1, 0);  glVertex3f( -halfEdge, -halfEdge, -halfEdge );
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
    glRotatef(atan(2*passo_x), 0, 0, 1);
    glRotatef(atan(2*passo_y), 0, 1, 0);
  SDL_GL_SwapWindow(window);
}

void Game::sokoReshape() {
  // TODO: atualizar screenWidth, screenHeight
  glViewport (0, 0, screenWidth, screenHeight);	//Changes the viewport to the whole window
  
  //sets projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLdouble)screenWidth/(GLdouble)screenHeight, 1.0, 10.0) ;
  glMatrixMode(GL_MODELVIEW);
}
