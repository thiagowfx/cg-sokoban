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
      glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

      /*glGenTextures(6, textureTargetIDs);
      for (int i=0; i<=5; i++){
        glBindTexture(GL_TEXTURE_2D, textureTargetIDs[i]);
        image = SOIL_load_image(targetPath[i], &width, &height,0, SOIL_LOAD_RGBA);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
      }

      glGenTextures(6, textureCharacterIDs);
      for (int i=0; i<=5; i++){
        glBindTexture(GL_TEXTURE_2D, textureCharacterIDs[i]);
        image = SOIL_load_image(characterPath[i], &width, &height,0, SOIL_LOAD_RGBA);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
      }

      glGenTextures(6, textureLightBoxIDs);
      for (int i=0; i<=5; i++){
        glBindTexture(GL_TEXTURE_2D, textureLightBoxIDs[i]);
        image = SOIL_load_image(lightBoxPath[i], &width, &height,0, SOIL_LOAD_RGBA);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
      }

      glGenTextures(6, textureHeavyBoxIDs);
      for (int i=0; i<=5; i++){
        glBindTexture(GL_TEXTURE_2D, textureHeavyBoxIDs[i]);
        image = SOIL_load_image(heavyBoxPath[i], &width, &height,0, SOIL_LOAD_RGBA);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
      }

      glGenTextures(6, textureWallIDs);
      for (int i=0; i<=5; i++){
        glBindTexture(GL_TEXTURE_2D, textureWallIDs[i]);
        image = SOIL_load_image(wallPath[i], &width, &height,0, SOIL_LOAD_RGBA);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
      }

      glGenTextures(6, textureFloorIDs);
      for (int i=0; i<=5; i++){
        glBindTexture(GL_TEXTURE_2D, textureFloorIDs[i]);
        image = SOIL_load_image(floorPath[i], &width, &height,0, SOIL_LOAD_RGBA);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
      }*/

      glGenTextures(1, &textureID);
      glBindTexture(GL_TEXTURE_2D, textureID);
      image = SOIL_load_image(path, &width, &height,0, SOIL_LOAD_RGBA);
      gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
      SOIL_free_image_data(image);


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
          drawCube(row, column, 0, size, 0/6);
        }
        else if (t == SokoObject::WALL) {
          drawCube(row, column, 0.5, size, 1/6);
          drawCube(row, column, 0, size, 1/6);
        }
        else {
          drawCube(row, column, 0, size, 2/6);
        }
      }
    }

    for (unsigned row = 0; row < board->getNumberOfRows(); row++) {
      for (unsigned column = 0; column < board->getNumberOfColumns(); column++) {
        SokoObject::Type u = board->getStatic(column, row).getType();
        SokoObject::Type t = board->getDynamic(column, row).getType();
        if (t == SokoObject::CHARACTER) {
          drawCube(row, column, 0.5, size, 3/6);
        }
        else if (t== SokoObject::LIGHT_BOX) {
          if(u == SokoObject::TARGET){
            color[1] = 0; //color is red
            color[2] = 0;
          }
          drawCube(row, column, 0.5, size, 4/6);
          color[1] = 1; //color is white again
          color[2] = 1;
        }
        else if (t == SokoObject::HEAVY_BOX) {
          if(u == SokoObject::TARGET){
            color[1] = 0; //color is red
            color[2] = 0;
          }
          drawCube(row, column, 0.5, size, 5/6);
          color[1] = 1; //color is white again
          color[2] = 1;
        }
      }
    }

    glFlush();
    SDL_GL_SwapWindow(window);
  }

  void Game::drawCube(GLdouble x, GLdouble y, GLdouble z, GLdouble edge, double tAxisPosition) {
    GLdouble halfEdge = edge / 2.0;
    GLfloat white[4] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);

    //For the t-axis
    double tB = tAxisPosition;
    double tT = tAxisPosition + 1/6;
    //glEnable(GL_TEXTURE_2D);        
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    /*drawing the cube*/
    glPushMatrix();
    glTranslatef(x * edge, y * edge, z);


    glBindTexture(GL_TEXTURE_2D, textureID);
    glBegin(GL_POLYGON);
    //Enables the texture for the bottom
    glNormal3f(0.0, 0.0, -1.0); glTexCoord2f(1/6,0); glVertex3f(  halfEdge, -halfEdge, -halfEdge );
    glNormal3f(0.0, 0.0, -1.0); glTexCoord2f(1/6,1); glVertex3f(  halfEdge,  halfEdge, -halfEdge );
    glNormal3f(0.0, 0.0, -1.0); glTexCoord2f(0/6,1); glVertex3f( -halfEdge,  halfEdge, -halfEdge );
    glNormal3f(0.0, 0.0, -1.0); glTexCoord2f(0/6,0); glVertex3f( -halfEdge, -halfEdge, -halfEdge );
    glEnd();

    //glBindTexture(GL_TEXTURE_2D, textureIDs[1]);   //Enables the texture for the top
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(2/6,0); glVertex3f(  halfEdge, -halfEdge, halfEdge );
    glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(2/6,1); glVertex3f(  halfEdge,  halfEdge, halfEdge );
    glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(1/6,1); glVertex3f( -halfEdge,  halfEdge, halfEdge );
    glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(1/6,0); glVertex3f( -halfEdge, -halfEdge, halfEdge );
    glEnd();

    //glBindTexture(GL_TEXTURE_2D, textureIDs[2]);  
    glBegin(GL_POLYGON);
    glNormal3f(1.0, 0.0, 0.0); glTexCoord2f(2/6,0); glVertex3f( halfEdge, -halfEdge, -halfEdge );
    glNormal3f(1.0, 0.0, 0.0); glTexCoord2f(3/6,0); glVertex3f( halfEdge,  halfEdge, -halfEdge );
    glNormal3f(1.0, 0.0, 0.0); glTexCoord2f(3/6,1); glVertex3f ( halfEdge,  halfEdge,  halfEdge );
    glNormal3f(1.0, 0.0, 0.0); glTexCoord2f(2/6,1); glVertex3f( halfEdge, -halfEdge,  halfEdge );
    glEnd();

    //glBindTexture(GL_TEXTURE_2D, textureIDs[3]);  
    glBegin(GL_POLYGON);
    glNormal3f(-1.0, 0.0, 0.0); glTexCoord2f(3/6,1); glVertex3f( -halfEdge, -halfEdge,  halfEdge );
    glNormal3f(-1.0, 0.0, 0.0); glTexCoord2f(4/6,1); glVertex3f( -halfEdge,  halfEdge,  halfEdge );
    glNormal3f(-1.0, 0.0, 0.0); glTexCoord2f(4/6,0); glVertex3f( -halfEdge,  halfEdge, -halfEdge );
    glNormal3f(-1.0, 0.0, 0.0); glTexCoord2f(3/6,0); glVertex3f( -halfEdge, -halfEdge, -halfEdge );
    glEnd();

    //glBindTexture(GL_TEXTURE_2D, textureIDs[4]);  
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0); glTexCoord2f(5/6,1); glVertex3f(  halfEdge,  halfEdge,  halfEdge );
    glNormal3f(0.0, 1.0, 0.0); glTexCoord2f(5/6,0); glVertex3f(  halfEdge,  halfEdge, -halfEdge );
    glNormal3f(0.0, 1.0, 0.0); glTexCoord2f(4/6,0); glVertex3f( -halfEdge,  halfEdge, -halfEdge );
    glNormal3f(0.0, 1.0, 0.0); glTexCoord2f(4/6,1); glVertex3f( -halfEdge,  halfEdge,  halfEdge ); 
    glEnd();

    //glBindTexture(GL_TEXTURE_2D, textureIDs[5]);   
    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0); glTexCoord2f(6/6,0); glVertex3f(  halfEdge, -halfEdge, -halfEdge );
    glNormal3f(0.0, -1.0, 0.0); glTexCoord2f(6/6,1); glVertex3f(  halfEdge, -halfEdge,  halfEdge );
    glNormal3f(0.0, -1.0, 0.0); glTexCoord2f(5/6,1); glVertex3f( -halfEdge, -halfEdge,  halfEdge );
    glNormal3f(0.0, -1.0, 0.0); glTexCoord2f(5/6,0); glVertex3f( -halfEdge, -halfEdge, -halfEdge );
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

  void Game::renderGameFinished() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D); 

    int width, height;
    bool hasAlpha;
    GLubyte* textureData;

    bool success = loadPngImage(GAME_END_IMAGE, width, height, hasAlpha, &textureData);
    if (!success) {
      SDL_Log("Unable to load png file");
      exit(EXIT_FAILURE);
    }
    else {
      SDL_Log("PNG Image loaded: %d x %d. Transparency? %d", width, height, hasAlpha);
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? 4 : 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glShadeModel(GL_FLAT);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glFlush();
    SDL_GL_SwapWindow(window);
  }

  void Game::moveDownAction() {
    board->move(Direction::DOWN);
    SDL_Log(board->toString().c_str());
  }

  void Game::moveUpAction() {
    board->move(Direction::UP);
    SDL_Log(board->toString().c_str());
  }

  void Game::moveLeftAction() {
    board->move(Direction::LEFT);
    SDL_Log(board->toString().c_str());
  }

  void Game::moveRightAction() {
    board->move(Direction::RIGHT);
    SDL_Log(board->toString().c_str());
  }

  void Game::undoAction() {
    board->undo();
    SDL_Log(board->toString().c_str());
  }
}

bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData) {
  png_structp png_ptr;
  png_infop info_ptr;
  unsigned int sig_read = 0;
  int color_type, interlace_type;
  FILE *fp;

  if ((fp = fopen(name, "rb")) == NULL)
    return false;

  /* Create and initialize the png_struct
   * with the desired error handler
   * functions.  If you want to use the
   * default stderr and longjump method,
   * you can supply NULL for the last
   * three parameters.  We also supply the
   * the compiler header file version, so
   * that we know if the application
   * was compiled with a compatible version
   * of the library.  REQUIRED
   */
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
      NULL, NULL, NULL);

  if (png_ptr == NULL) {
    fclose(fp);
    return false;
  }

  /* Allocate/initialize the memory
   * for image information.  REQUIRED. */
  info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == NULL) {
    fclose(fp);
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    return false;
  }

  /* Set error handling if you are
   * using the setjmp/longjmp method
   * (this is the normal method of
   * doing things with libpng).
   * REQUIRED unless you  set up
   * your own error handlers in
   * the png_create_read_struct()
   * earlier.
   */
  if (setjmp(png_jmpbuf(png_ptr))) {
    /* Free all of the memory associated
     * with the png_ptr and info_ptr */
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(fp);
    /* If we get here, we had a
     * problem reading the file */
    return false;
  }

  /* Set up the output control if
   * you are using standard C streams */
  png_init_io(png_ptr, fp);

  /* If we have already
   * read some of the signature */
  png_set_sig_bytes(png_ptr, sig_read);

  /*
   * If you have enough memory to read
   * in the entire image at once, and
   * you need to specify only
   * transforms that can be controlled
   * with one of the PNG_TRANSFORM_*
   * bits (this presently excludes
   * dithering, filling, setting
   * background, and doing gamma
   * adjustment), then you can read the
   * entire image (including pixels)
   * into the info structure with this
   * call
   *
   * PNG_TRANSFORM_STRIP_16 |
   * PNG_TRANSFORM_PACKING  forces 8 bit
   * PNG_TRANSFORM_EXPAND forces to
   *  expand a palette into RGB
   */
  png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

  png_uint_32 width, height;
  int bit_depth;
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
      &interlace_type, NULL, NULL);
  outWidth = width;
  outHeight = height;

  unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
  *outData = (unsigned char*) malloc(row_bytes * outHeight);

  png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

  for (int i = 0; i < outHeight; i++) {
    // note that png is ordered top to
    // bottom, but OpenGL expect it bottom to top
    // so the order or swapped
    memcpy(*outData+(row_bytes * (outHeight-1-i)), row_pointers[i], row_bytes);
  }

  /* Clean up after the read,
   * and free any memory allocated */
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

  /* Close the file */
  fclose(fp);

  /* That's it */
  return true;
}

