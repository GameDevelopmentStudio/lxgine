#include "LXGame.h"
#include "LXGameState.h"
#include "LXInput.h"

#include <time.h>

// ESC key
#define ESCAPE 27

#pragma mark - Memory Management

LXGame::LXGame() {
  glut = LXGlut::sharedInstance();
  LXGlut::retain();
  input = glut->input;
  world = NULL;
}

LXGame::~LXGame() {
  if (world) {
    delete world;
  }
  LXGlut::release();
}

#pragma mark - Initialization Methods

void LXGame::init(int argc, char **argv) {
  // Set game general properties
  initSettings();

  glut->game = this;
  glut->init(argc, argv);

  // Set seed here (who knows what we'll need)
  srand((unsigned int)time(NULL));
}

void LXGame::run() {
  // Asks glut to start the run loop
  // From hereon, this instance of LXGame will receive event calls from glut
  glut->run();
}

#pragma mark - Main Virtual Methods

void LXGame::initSettings() {
  width = 640;
  height = 480;
}

void LXGame::render() {

}

void LXGame::update() {
  // If escape is pressed, close everything
  if (input->keyPressed(ESCAPE)) { 
    glut->close();          
  } else if (input->specialKeyPressed(GLUT_KEY_F4)) {
    glut->toggleFullscreen();
  }
}

#pragma mark - GameState transition

void LXGame::changeWorld(LXGameState *newWorld) {
  if (world) {
    delete world;
  }

  world = newWorld;
  world->game = this;
  world->init();
}

#pragma mark - GLUT Events

void LXGame::Render() {
  // Clear the screen and the depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  render();

  if (world)
    world->render();

  // TODO:
  // transitions here

  // Since this is double buffered, swap the buffers 
  // to display what just got drawn.
  glutSwapBuffers();
}

void LXGame::Update() {
  // TODO: world change here
  // TODO: framerate
  
  input->update();
  update();

  if (world)
    world->update();
}

void LXGame::Resize(int width, int height) {
  // Prevent division by zero if the window is too small
  if (height == 0)
    height = 1;

  double glViewportOriginX, glViewportOriginY, glViewportWidth, glViewportHeight;
  double desiredGameAspectRatio = (float)this->width/(float)this->height;
  double viewPortAspectRatio = (float)width/(float)height;
  if (desiredGameAspectRatio >= viewPortAspectRatio) {
    // Update glViewport size to match window's width
    glViewportWidth = width;
    glViewportHeight = width / desiredGameAspectRatio;
    glViewportOriginX = 0;
    glViewportOriginY = height/2.f - glViewportHeight/2.f;
  } else {
    // Update glViewport size to match window's height
    glViewportWidth = height * desiredGameAspectRatio;
    glViewportHeight = height;
    glViewportOriginX = width/2.f - glViewportWidth/2.f;
    glViewportOriginY = 0;
  }  
  // Reset The Current Viewport And Perspective Transformation
  glViewport(glViewportOriginX,
             glViewportOriginY, 
             glViewportWidth,
             glViewportHeight);
}
