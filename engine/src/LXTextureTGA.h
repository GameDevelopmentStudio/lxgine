#ifndef __LXTEXTURETGA_H__
#define __LXTEXTURETGA_H__

#include "LXTexture.h"

class LXTextureTGA : public LXTexture{
 public:    
  LXTextureTGA();
  ~LXTextureTGA();

  void initWithPath(const char *path);
 
 private:
  unsigned char* newStringWithTGAFile(const char* filename, int &width, int &height);
};

#endif
