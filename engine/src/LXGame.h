#ifndef __LXGAME_H__
#define __LXGAME_H__

#include "LXGlut.h"

class LXGameState;

class LXGame {
 public:    
  // Not owned pointers
  LXInput *input;
  //
  // Owned pointers
  LXGameState *world;
  
  // Getters
  int getWidth();
  int getHeight();

  LXGame();
  virtual ~LXGame();

  virtual void initSettings();
  virtual void render();
  virtual void update();

  virtual void init(int argc, char **argv);
  virtual void run();
  virtual void changeWorld(LXGameState *newWorld);
  virtual void screenshot();

  // Event calls from glut
  virtual void Render();
  virtual void Update();
  virtual void Resize(int width, int height);

 protected:
  int width;
  int height;
  // OpenGL's window manager
  LXGlut *glut;
};

#endif
