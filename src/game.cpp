#include "game.hpp"

namespace Sokoban {
  Game::Game(SDL_Window* window, SDL_GLContext* glContext, int screenWidth, int screenHeight, TTF_Font* windowFont, SDL_Renderer* windowRenderer) :
    window(window),
    glContext(glContext),
    screenWidth(screenWidth),
    screenHeight(screenHeight),
    windowFont(windowFont),
    windowRenderer(windowRenderer) {

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
      glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
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
    // Clear.
    glClearColor(230/255.0, 212/255.0, 143/255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Objects drawing.
    glMatrixMode(GL_MODELVIEW);
    const double size = 0.5;

    // Drawing static objects
    for (unsigned row = 0; row < board->getNumberOfRows(); row++) {
      for (unsigned column = 0; column < board->getNumberOfColumns(); column++) {
        SokoObject::Type t = board->getStatic(column, row).getType();
        if (t == SokoObject::EMPTY) {
          drawCube(scale*row, scale*column, 0, size, textureFloorIDs);
        }
        else if (t == SokoObject::WALL) {
          drawCube(scale*row, scale*column, scale*0.5, size, textureWallIDs);
          drawCube(scale*row, scale*column, 0, size, textureFloorIDs);
        }
        else {
          drawCube(scale*row, scale*column, 0, size, textureTargetIDs);
        }
      }
    }

    // Drawing dynamic objects
    for (auto obj : board->getDynamic()) {
      auto t = obj.getType();
      SokoObject::Type u = board->getStatic(obj.getPosition().x, obj.getPosition().y).getType();
      if (t == SokoObject::CHARACTER) {
        drawCube(obj.positionY, obj.positionX, 0.5, size, textureCharacterIDs);
      }
      else if (t== SokoObject::LIGHT_BOX) {
        if(u == SokoObject::TARGET){
          color[1] = 0; // color is red
          color[2] = 0;
          glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        }
        drawCube(obj.positionY, obj.positionX, 0.5, size, textureLightBoxIDs);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
      }
      else if (t == SokoObject::HEAVY_BOX) {
        if(u == SokoObject::TARGET){
          color[1] = 0; // color is red
          color[2] = 0;
          glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        }
        drawCube(obj.positionY, obj.positionX, 0.5, size, textureHeavyBoxIDs);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
      }
    }
    color[1] = 1; // color is white again
    color[2] = 1;

    board->update(0.05);
    // Statusbar
    stringstream ss;
    ss.clear();
    ss << "Stage: " << getCurrentLevel();
    ss << " | Moves: " << board->getNumberOfMoves();
    ss << " | Light boxes: " << board->getNumberOfUnresolvedLightBoxes();
    ss << " | Heavy boxes: " << board->getNumberOfUnresolvedHeavyBoxes();
    renderStatusbar(ss.str(), SDL_Color{255, 255, 255, 255});
    
    glFlush();
    SDL_GL_SwapWindow(window);
  }

  void Game::renderStatusbar(std::string text, SDL_Color textColor) {
    SDL_Surface* surface = TTF_RenderText_Solid(windowFont, text.c_str(), textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(windowRenderer, surface);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); 
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    // Disabling depth test for 2d rendering
    glDisable(GL_DEPTH_TEST);

    // Setting the viewport
    //glViewport(0, 0, screenWidth/2, screenHeight/10);
    glViewport(0, 0, screenWidth, screenHeight/20);

    //Binding the texture
    float width, height;
    float x = -1.0, y = -1.0;
    SDL_GL_BindTexture(texture, &width, &height);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0 * height);         glVertex2f(x, y);
    glTexCoord2f(1.0 * width, 1.0 * height); glVertex2f(x + 2.0, y);
    glTexCoord2f(1.0 * width, 0.0);          glVertex2f(x + 2.0, y + 2.0);
    glTexCoord2f(0.0, 0.0);                  glVertex2f(x, y + 2.0);
    glEnd();

    // Cleaning the used data structures
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, screenWidth, screenHeight);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();    
    SDL_GL_UnbindTexture(texture);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
  }

  void Game::drawCube(GLdouble x, GLdouble y, GLdouble z,
                      GLdouble edge, GLuint* textureIDs) {

    GLdouble halfEdge = scale*(edge / 2.0);

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
    currentLevel = level;
    stringstream ss;
    ss << "assets/stages/stage" << currentLevel << ".sok";
    board = new SokoBoard(ss.str());
  }

  bool Game::isLevelFinished() const {
    return board->isFinished();
  }

  void Game::renderSingleImage(const char* path) {
    SDL_Surface* loadedSurface = IMG_Load(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(windowRenderer, loadedSurface);    
    
    // Starting the matrixes.
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); 
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);

    float width, height;
    float x = -1.0, y = -1.0;
    SDL_GL_BindTexture(texture, &width, &height);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0 * height);         glVertex2f(x, y);
    glTexCoord2f(1.0 * width, 1.0 * height); glVertex2f(x + 2.0, y);
    glTexCoord2f(1.0 * width, 0.0);          glVertex2f(x + 2.0, y + 2.0);
    glTexCoord2f(0.0, 0.0);                  glVertex2f(x, y + 2.0);
    glEnd();

    // Popping the matrixes
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glFlush();
    SDL_GL_SwapWindow(window);

    SDL_GL_UnbindTexture(texture);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(loadedSurface);
  }

  void Game::changeScale(int n) {
    if (n == 1) {
      scale *= 1.05;
    }
    else {
      scale *= 0.95;
    }
  }

  SokoBoard* Game::getGameBoard() const {
    return board;
  }

  unsigned Game::getCurrentLevel() const {
    return currentLevel;
  }

  bool Game::moveDownAction() {
    return board->move(Direction::DOWN);
  }

  bool Game::moveUpAction() {
    return board->move(Direction::UP);
  }

  bool Game::moveLeftAction() {
    return board->move(Direction::LEFT);
  }

  bool Game::moveRightAction() {
    return board->move(Direction::RIGHT);
  }

  bool Game::undoAction() {
    return board->undo();
  }
}
