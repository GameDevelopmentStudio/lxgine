#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "LXGlut.h"
#include "LXGameState.h"

class LXEntity;

class Level : public LXGameState {
 public:    
  LXEntity *exampleEntity;
  GLfloat light0Pos[4];

  Level();
  ~Level();

  void init();

  void render();
  void update();
};

#endif
