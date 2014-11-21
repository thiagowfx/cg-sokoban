#include "game.hpp"

Game::Game(SDL_Window* window, SDL_GLContext* glContext, int screenWidth, int screenHeight) :
  window(window),
  glContext(glContext),
  screenWidth(screenWidth),
  screenHeight(screenHeight) {

    /* Set OpenGL attributes. */
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
      LOG_SDL_DIE("OpenGL context could not be created");
    }

    /* Enable VSync. */
    //if(SDL_GL_SetSwapInterval(1) < 0) {
      //sdldie("Warning: Unable to set VSync");
    //}

    /* Enable Z-Depth. */
    glEnable(GL_DEPTH_TEST);

    /* Normalizes the normal vectors of every vertex (ie. size = 1) */
    glEnable(GL_NORMALIZE);
  
    /* Shading model is smooth. */
    glShadeModel(GL_SMOOTH);

    /* Enable Lighting. */
    glEnable(GL_LIGHTING);

    /* Clean the background and sets it to the RGB parameters. */
    glClearColor(0.5, 0.5, 0.5, 1.0);

    /* Set the Projection Matrix to the Identity. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* Define the camera's properties: where it is, where it's looking at, its up vector. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* Camera initial position. */
    gluLookAt(4.0, 4.0, 2.0, // eye
              0, 0, 0,       // lookAt
              0, -0.1, 1);   // up

    sokoReshape();
  }

Game::~Game() {
  delete board;
  board = NULL;
}

void Game::renderScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /*Ambient's lighting - eg. Light all around despite the light sources*/
  GLfloat ambientIntesity[4] = {1.5, 1.5, 1.5, 1.0};          //Ambient's light is white
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientIntesity);

  /*Light source number 0*/
  GLfloat light0Intensity[4] = {0, 1, 0, 1.0};                 //Light0 is green
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Intensity);           //For diffuse reflection
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0Intensity);          //For specular reflection
  GLfloat light0Position[4] = {1, 1, 0, 0};                    //Light0's position
  glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
  glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0);             //Attenuation
  glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0); 
  glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1);
  glEnable(GL_LIGHT0);

  /*Light source number 1*/
  GLfloat light1Intensity[4] = {1.0, 0, 0, 1.0};               //Light1 is red
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Intensity);           //For diffuse reflection
  glLightfv(GL_LIGHT1, GL_SPECULAR, light1Intensity);          //For specular reflection
  GLfloat light1Position[4] = {1, 0, 1, 0};                    //Light1's position
  glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
  glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0);             //Attenuation
  glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0); 
  glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.1);
  glEnable(GL_LIGHT1);

  /*Light source number 1*/
  GLfloat light2Intensity[4] = {1.0, 1.0, 0, 1.0};             //Light2 color
  glLightfv(GL_LIGHT2, GL_DIFFUSE, light2Intensity);           //For diffuse reflection
  glLightfv(GL_LIGHT2, GL_SPECULAR, light2Intensity);          //For specular reflection
  GLfloat light2Position[4] = {0, 1, 1, 0};                    //Light2's position
  glLightfv(GL_LIGHT2, GL_POSITION, light2Position);
  glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0);             //Attenuation
  glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0); 
  glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.1);
  glEnable(GL_LIGHT2);


  /*Objects drawing*/
  glMatrixMode(GL_MODELVIEW);
  const double size = 0.5;

  for (unsigned row = 0; row < board->staticBoard.size(); ++row) {
    for (unsigned column = 0; column < board->staticBoard[0].size(); ++column) {
      SokoObject::Type t = board->staticBoard[row][column].getType();
      if (t == SokoObject::EMPTY) {
        drawCube(row, column, 0, size);
      }
      else if (t == SokoObject::CHARACTER) {
        drawCube(row, column, 0, size);
      }
      else if (t== SokoObject::LIGHT_BOX) {
        drawCube(row, column, 0, size);
      }
      else if (t == SokoObject::HEAVY_BOX) {
        drawCube(row, column, 0, size);
      }
      else if (t == SokoObject::WALL) {
        drawCube(row, column, 0, size);
      }
      else {
         drawCube(row, column, 0, size);
      }
    }
  }
  glFlush();
  SDL_GL_SwapWindow(window);
}

void Game::drawCube(GLdouble x, GLdouble y, GLdouble z, GLdouble edge)
{
  /* This function draws a cube of size (edge x edge x edge) centered at position (x, y, z)*/
  GLdouble halfEdge = edge/2;
  glEnable(GL_TEXTURE_2D);

  /*coloring the cube*/
  GLfloat color[4] = {0, 0.3, 1, 1};                                      //Cube's color
  GLfloat white[4] = {1, 1, 1, 1};                                        //White
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);         //Ambient and diffuse reflections
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);                    //Specular reflection
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);                      //Shininess is 100

  glPushMatrix();
  glTranslatef(x*edge, y*edge, z);

  glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);  glVertex3f(  halfEdge, -halfEdge, -halfEdge );
    glNormal3f(0, 0, -1);  glVertex3f(  halfEdge,  halfEdge, -halfEdge );
    glNormal3f(0, 0, -1);  glVertex3f( -halfEdge,  halfEdge, -halfEdge );
    glNormal3f(0, 0, -1);  glVertex3f( -halfEdge, -halfEdge, -halfEdge );
  glEnd();

  glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);  glVertex3f(  halfEdge, -halfEdge, halfEdge );
    glNormal3f(0, 0, 1);  glVertex3f(  halfEdge,  halfEdge, halfEdge );
    glNormal3f(0, 0, 1);  glVertex3f( -halfEdge,  halfEdge, halfEdge );
    glNormal3f(0, 0, 1);  glVertex3f( -halfEdge, -halfEdge, halfEdge );
  glEnd();

  glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);  glVertex3f( halfEdge, -halfEdge, -halfEdge );
    glNormal3f(1, 0, 0);  glVertex3f( halfEdge,  halfEdge, -halfEdge );
    glNormal3f(1, 0, 0);  glVertex3f( halfEdge,  halfEdge,  halfEdge );
    glNormal3f(1, 0, 0);  glVertex3f( halfEdge, -halfEdge,  halfEdge );
  glEnd();

  glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);  glVertex3f( -halfEdge, -halfEdge,  halfEdge );
    glNormal3f(-1, 0, 0);  glVertex3f( -halfEdge,  halfEdge,  halfEdge );
    glNormal3f(-1, 0, 0);  glVertex3f( -halfEdge,  halfEdge, -halfEdge );
    glNormal3f(-1, 0, 0);  glVertex3f( -halfEdge, -halfEdge, -halfEdge );
  glEnd();

  glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);  glVertex3f(  halfEdge,  halfEdge,  halfEdge );
    glNormal3f(0, 1, 0);  glVertex3f(  halfEdge,  halfEdge, -halfEdge );
    glNormal3f(0, 1, 0);  glVertex3f( -halfEdge,  halfEdge, -halfEdge );
    glNormal3f(0, 1, 0);  glVertex3f( -halfEdge,  halfEdge,  halfEdge ); 
  glEnd();

  glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);  glVertex3f(  halfEdge, -halfEdge, -halfEdge );
    glNormal3f(0, -1, 0);  glVertex3f(  halfEdge, -halfEdge,  halfEdge );
    glNormal3f(0, -1, 0);  glVertex3f( -halfEdge, -halfEdge,  halfEdge );
    glNormal3f(0, -1, 0);  glVertex3f( -halfEdge, -halfEdge, -halfEdge );
  glEnd();

  glFlush();
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
  gluPerspective(40.0, (GLdouble)screenWidth/(GLdouble)screenHeight, 1.0, 10.0) ;
  glMatrixMode(GL_MODELVIEW);
}

void Game::loadLevel(const unsigned level) {
  if (board != NULL) {
    delete board;
    board = NULL;
  }
  stringstream ss;
  ss << "assets/stages/stage" << level << ".sok";
  board = new SokoBoard(ss.str());
}

bool Game::isLevelFinished() const {
  return board->isFinished();
}

void Game::renderGameFinished() {
  glClearColor(0.0, 0.0, 0.75, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glFlush();
  SDL_GL_SwapWindow(window);
}
