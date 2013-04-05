// Check this one
/* #define GLUT_DISABLE_ATEXIT_HACK */

#include "LXGlut.h"
#include "LXGame.h"
#include "LXInput.h"

#include <stdlib.h>

#pragma mark - Static Initializations

LXGlut *LXGlut::instance = 0;
int LXGlut::retainCount = 0;

#pragma mark - Memory Management
// TODO: make threadsafe

LXGlut *LXGlut::sharedInstance() {
  if (!instance) {
    instance = new LXGlut();
  }
  return instance;
}

void LXGlut::retain() {
  LXGlut::retainCount++;
}

void LXGlut::release() {
  if (retainCount > 0) {
    LXGlut::retainCount--;
    if (retainCount == 0) {
      delete instance;
    }
  }
}

LXGlut::LXGlut() {
  input = new LXInput();
}

LXGlut::~LXGlut() {
  delete input;
}

void LXGlut::init(int argc, char **argv) {
  // Initialize GLUT state - glut will take any command line arguments that pertain to it
  glutInit(&argc, argv);  

  // Select type of Display mode:   
  // Double buffer 
  // RGBA color
  // Alpha components supported 
  // Depth buffer
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  

  glutInitWindowSize(game->getWidth(), game->getHeight());
  glutInitWindowPosition(0, 0);  
  window = glutCreateWindow("Batman was not here");
  fullscreen = false;

  glewExperimental = GL_TRUE;
  glewInit();

  // Register the callback to do all our OpenGL drawing.
  glutDisplayFunc(&renderWindow);  
  // Register the callback when our window is resized.
  glutReshapeFunc(&resizeWindow);
  // Register input callbacks
  glutKeyboardFunc(&keyPressed);
  glutKeyboardUpFunc(&keyReleased);
  glutSpecialFunc(&specialKeyPressed);
  glutSpecialUpFunc(&specialKeyReleased);
}

#pragma mark - Runloop Methods

void LXGlut::run() {
  // Set up the runloop
  glutTimerFunc(33.3f, &step, 0);
  glutMainLoop();
}

void LXGlut::step(int frame) {
  instance->game->Update();
  instance->game->Render();
  
  glutTimerFunc(33.3f, &LXGlut::step, frame + 1);
}

#pragma mark - Window methods

void LXGlut::resizeWindow(int width, int height) {
  instance->game->Resize(width, height);
}

void LXGlut::renderWindow() {
  instance->game->Render();
}

void LXGlut::close() {
  // Shut down the window
  glutDestroyWindow(instance->window); 
  
  // Exit application with normal termination
  exit(0);
}

void LXGlut::toggleFullscreen() {
  if (fullscreen)
    glutReshapeWindow(game->getWidth(), game->getHeight());
  else
    glutFullScreen();

  fullscreen = !fullscreen;
}

bool LXGlut::isFullscreen() {
  return fullscreen;
}

#pragma mark - Input Methods

void LXGlut::specialKeyReleased(int key, int x, int y) {
  instance->input->specialKeyStates[key] = false;
}

void LXGlut::specialKeyPressed(int key, int x, int y) {
  instance->input->specialKeyStates[key] = true;
}

void LXGlut::keyReleased(unsigned char key, int x, int y) {
  instance->input->keyStates[key] = false;
}

void LXGlut::keyPressed(unsigned char key, int x, int y) {
  instance->input->keyStates[key] = true;
}
