#ifndef __DERAI_H__
#define __DERAI_H__

#include "LXGame.h"

class Derai : public LXGame {
 public:    
  Derai();
  ~Derai();

  void initSettings();

  void init(int argc, char **argv);
};

#endif
