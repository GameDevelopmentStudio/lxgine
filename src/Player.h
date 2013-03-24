#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "LXEntity.h"
#include "LXGlut.h"

class Player : public LXEntity {
 public:
  GLuint vertexArray;
  GLuint vertexBuffer;
  
  Player();
  ~Player();

  void init();
  void render();
};

#endif
