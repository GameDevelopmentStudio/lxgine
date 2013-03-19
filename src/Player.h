#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "LXEntity.h"

class Player : public LXEntity {
 public:
  Player();
  ~Player();

  void init();
  void render();
};

#endif
