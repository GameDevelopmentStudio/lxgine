#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "LXGlut.h"
#include "LXGameState.h"

class LXEntity;
class LXShader;
class LXTexture;

class Level : public LXGameState {
 public:    
   
  LXShader *floorProg;
  LXShader *objProg;
  LXTexture *floorTex;
  
  LXEntity *exampleEntity;
  GLfloat light0Pos[4];

  Level();
  ~Level();

  void init();

  void render();
  void update();
};

#endif
