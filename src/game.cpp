#include "game.hpp"

namespace Sokoban {
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

      /* Enable Z-Depth. */
      glEnable(GL_DEPTH_TEST);

      /* Normalizes the normal vectors of every vertex (ie. size = 1) */
      glEnable(GL_NORMALIZE);

      /* Shading model is smooth. */
      glShadeModel(GL_SMOOTH);

      /* Enable Lighting. */
      glEnable(GL_LIGHTING);

      /* Global ambient illumination. */
      GLfloat globalAmbientIntensity[4] = {1.5, 1.5, 1.5, 1.0};
      glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientIntensity);

      /* LIGHT0 .*/
      glEnable(GL_LIGHT0);
      GLfloat light0Intensity[4] = {0.0, 1.0, 0.0, 1.0};
      glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0Intensity);
      glLightfv(GL_LIGHT0, GL_SPECULAR, light0Intensity);
      GLfloat light0Position[4] = {1.0, 1.0, 0.0, 0.0};
      glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
      glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);
      glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0); 
      glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1);

      /* LIGHT1 .*/
      glEnable(GL_LIGHT1);
      GLfloat light1Intensity[4] = {1.0, 0, 0, 1.0};
      glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1Intensity);
      glLightfv(GL_LIGHT1, GL_SPECULAR, light1Intensity);
      GLfloat light1Position[4] = {1.0, 0.0, 1.0, 0.0};
      glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
      glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0); 
      glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0); 
      glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.1);

      /* LIGHT2. */
      glEnable(GL_LIGHT2);
      GLfloat light2Intensity[4] = {1.0, 1.0, 0.0, 1.0};
      glLightfv(GL_LIGHT2, GL_DIFFUSE, light2Intensity);
      glLightfv(GL_LIGHT2, GL_SPECULAR, light2Intensity);
      GLfloat light2Position[4] = {0.0, 1.0, 1.0, 0.0};
      glLightfv(GL_LIGHT2, GL_POSITION, light2Position);
      glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0);
      glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.0); 
      glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.1);

      /*Generating Textures*/

      unsigned char* image;
      int width, height;
      glEnable(GL_TEXTURE_2D);        
      glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
      glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

      glGenTextures(6, textureTargetIDs);
      for (int i=0; i<=5; i++){
        glBindTexture(GL_TEXTURE_2D, textureTargetIDs[i]);
        image = SOIL_load_image(targetPath[i], &width, &height,0, SOIL_LOAD_RGBA);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
      }

      glGenTextures(6, textureCharacterIDs);
      for (int i=0; i<=5; i++){
        glBindTexture(GL_TEXTURE_2D, textureCharacterIDs[i]);
        image = SOIL_load_image(characterPath[i], &width, &height,0, SOIL_LOAD_RGBA);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
      }

      glGenTextures(6, textureLightBoxIDs);
      for (int i=0; i<=5; i++){
        glBindTexture(GL_TEXTURE_2D, textureLightBoxIDs[i]);
        image = SOIL_load_image(lightBoxPath[i], &width, &height,0, SOIL_LOAD_RGBA);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
      }

      glGenTextures(6, textureHeavyBoxIDs);
      for (int i=0; i<=5; i++){
        glBindTexture(GL_TEXTURE_2D, textureHeavyBoxIDs[i]);
        image = SOIL_load_image(heavyBoxPath[i], &width, &height,0, SOIL_LOAD_RGBA);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
      }

      glGenTextures(6, textureWallIDs);
      for (int i=0; i<=5; i++){
        glBindTexture(GL_TEXTURE_2D, textureWallIDs[i]);
        image = SOIL_load_image(wallPath[i], &width, &height,0, SOIL_LOAD_RGBA);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
      }

      glGenTextures(6, textureFloorIDs);
      for (int i=0; i<=5; i++){
        glBindTexture(GL_TEXTURE_2D, textureFloorIDs[i]);
        image = SOIL_load_image(floorPath[i], &width, &height,0, SOIL_LOAD_RGBA);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
      }

      //std::cout << textureTargetIDs[0] << " " << textureFloorIDs[1] << " " << textureFloorIDs[5] << std::endl;
      /* Clean the background and sets it to the RGB parameters. */
      glClearColor(0.5, 0.5, 0.5, 1.0);

      /* Set the Projection Matrix to the Identity. */
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      /* Camera initial position. */
      gluLookAt(4.0, 4.0, 2.0, // eye
          0.0, 0.0, 0.0,             // lookAt
          0.0, -0.1, 1);         // up

      sokoReshape();
    }

  Game::~Game() {
    delete board;
    board = NULL;
  }

  void Game::renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*Objects drawing*/
    glMatrixMode(GL_MODELVIEW);
    const double size = 0.5;


    for (unsigned row = 0; row < board->getNumberOfRows(); row++) {
      for (unsigned column = 0; column < board->getNumberOfColumns(); column++) {
        SokoObject::Type t = board->getStatic(column, row).getType();
        if (t == SokoObject::EMPTY) {
          drawCube(row, column, 0, size, textureFloorIDs);
        }
        else if (t == SokoObject::WALL) {
          drawCube(row, column, 0.5, size, textureWallIDs);
          drawCube(row, column, 0, size, textureFloorIDs);
        }
        else {
          drawCube(row, column, 0, size, textureTargetIDs);
        }
      }
    }

    for (unsigned row = 0; row < board->getNumberOfRows(); row++) {
      for (unsigned column = 0; column < board->getNumberOfColumns(); column++) {
        SokoObject::Type u = board->getStatic(column, row).getType();
        SokoObject::Type t = board->getDynamic(column, row).getType();
        if (t == SokoObject::CHARACTER) {
          drawCube(row, column, 0.5, size, textureCharacterIDs);
        }
        else if (t== SokoObject::LIGHT_BOX) {
          if(u == SokoObject::TARGET){
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
          }
          drawCube(row, column, 0.5, size, textureLightBoxIDs);
          glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        }
        else if (t == SokoObject::HEAVY_BOX) {
          if(u == SokoObject::TARGET){
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
          }
          drawCube(row, column, 0.5, size, textureHeavyBoxIDs);
          glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        }
      }
    }

    glFlush();
    SDL_GL_SwapWindow(window);
  }

  void Game::drawCube(GLdouble x, GLdouble y, GLdouble z, GLdouble edge, GLuint* textureIDs) {
    GLdouble halfEdge = edge / 2.0;
    GLfloat color[4] = {1.0, 0.0, 0.0, 1.0}; //color is red
    GLfloat white[4] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);


    //glEnable(GL_TEXTURE_2D);        
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    /*drawing the cube*/
    glPushMatrix();
    glTranslatef(x * edge, y * edge, z);


    glBindTexture(GL_TEXTURE_2D, textureIDs[0]);
    glBegin(GL_POLYGON);
    //Enables the texture for the bottom
    glNormal3f(0.0, 0.0, -1.0); glTexCoord2f(1,0); glVertex3f(  halfEdge, -halfEdge, -halfEdge );
    glNormal3f(0.0, 0.0, -1.0); glTexCoord2f(1,1); glVertex3f(  halfEdge,  halfEdge, -halfEdge );
    glNormal3f(0.0, 0.0, -1.0); glTexCoord2f(0,1); glVertex3f( -halfEdge,  halfEdge, -halfEdge );
    glNormal3f(0.0, 0.0, -1.0); glTexCoord2f(0,0); glVertex3f( -halfEdge, -halfEdge, -halfEdge );
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textureIDs[1]);   //Enables the texture for the top
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(1,0); glVertex3f(  halfEdge, -halfEdge, halfEdge );
    glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(1,1); glVertex3f(  halfEdge,  halfEdge, halfEdge );
    glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(0,1); glVertex3f( -halfEdge,  halfEdge, halfEdge );
    glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(0,0); glVertex3f( -halfEdge, -halfEdge, halfEdge );
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textureIDs[2]);  
    glBegin(GL_POLYGON);
    glNormal3f(1.0, 0.0, 0.0); glTexCoord2f(0,0); glVertex3f( halfEdge, -halfEdge, -halfEdge );
    glNormal3f(1.0, 0.0, 0.0); glTexCoord2f(1,0); glVertex3f( halfEdge,  halfEdge, -halfEdge );
    glNormal3f(1.0, 0.0, 0.0); glTexCoord2f(1,1); glVertex3f ( halfEdge,  halfEdge,  halfEdge );
    glNormal3f(1.0, 0.0, 0.0); glTexCoord2f(0,1); glVertex3f( halfEdge, -halfEdge,  halfEdge );
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textureIDs[3]);  
    glBegin(GL_POLYGON);
    glNormal3f(-1.0, 0.0, 0.0); glTexCoord2f(0,1); glVertex3f( -halfEdge, -halfEdge,  halfEdge );
    glNormal3f(-1.0, 0.0, 0.0); glTexCoord2f(1,1); glVertex3f( -halfEdge,  halfEdge,  halfEdge );
    glNormal3f(-1.0, 0.0, 0.0); glTexCoord2f(1,0); glVertex3f( -halfEdge,  halfEdge, -halfEdge );
    glNormal3f(-1.0, 0.0, 0.0); glTexCoord2f(0,0); glVertex3f( -halfEdge, -halfEdge, -halfEdge );
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textureIDs[4]);  
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0); glTexCoord2f(1,1); glVertex3f(  halfEdge,  halfEdge,  halfEdge );
    glNormal3f(0.0, 1.0, 0.0); glTexCoord2f(1,0); glVertex3f(  halfEdge,  halfEdge, -halfEdge );
    glNormal3f(0.0, 1.0, 0.0); glTexCoord2f(0,0); glVertex3f( -halfEdge,  halfEdge, -halfEdge );
    glNormal3f(0.0, 1.0, 0.0); glTexCoord2f(0,1); glVertex3f( -halfEdge,  halfEdge,  halfEdge ); 
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textureIDs[5]);   
    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0); glTexCoord2f(1,0); glVertex3f(  halfEdge, -halfEdge, -halfEdge );
    glNormal3f(0.0, -1.0, 0.0); glTexCoord2f(1,1); glVertex3f(  halfEdge, -halfEdge,  halfEdge );
    glNormal3f(0.0, -1.0, 0.0); glTexCoord2f(0,1); glVertex3f( -halfEdge, -halfEdge,  halfEdge );
    glNormal3f(0.0, -1.0, 0.0); glTexCoord2f(0,0); glVertex3f( -halfEdge, -halfEdge, -halfEdge );
    glEnd();

    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
  }

  void Game::setOldPosition(GLdouble x, GLdouble y) {
    this->xold = x;
    this->yold = y;
  }

  void Game::setNewPosition(GLdouble xnew, GLdouble ynew) {
    GLint xstep = xnew - xold;
    GLint ystep = ynew - yold;
    setOldPosition(xnew, ynew);

    glMatrixMode(GL_MODELVIEW);
    glRotatef(atan(2.0 * xstep), 0.0, 0.0, 1.0);
    glRotatef(atan(2.0 * ystep), 0.0, 1.0, 0.0);

    glFlush();
    SDL_GL_SwapWindow(window);
  }

  void Game::sokoReshape() {
    /* Viewport: whole window. */
    glViewport(0.0, 0.0, screenWidth, screenHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, GLdouble(screenWidth)/screenHeight, 1.0, 10.0) ;

    glMatrixMode(GL_MODELVIEW);
  }

  void Game::setWindowSize(unsigned width, unsigned height) {
    this->screenWidth = width;
    this->screenHeight = height;
    sokoReshape();
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

  void Game::renderSingleImage(const char* path) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    unsigned char* image;
    int width, height;
    glEnable(GL_TEXTURE_2D);

    image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, -1.0, 0.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, -1.0, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glFlush();
    SDL_GL_SwapWindow(window);
  }

  SokoBoard* Game::getGameBoard() const {
    return board;
  }

  void Game::moveDownAction() {
    board->move(Direction::DOWN);
  }

  void Game::moveUpAction() {
    board->move(Direction::UP);
  }

  void Game::moveLeftAction() {
    board->move(Direction::LEFT);
  }

  void Game::moveRightAction() {
    board->move(Direction::RIGHT);
  }

  void Game::undoAction() {
    board->undo();
  }
}
