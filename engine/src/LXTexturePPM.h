#ifndef __LXTEXTUREPPM_H__
#define __LXTEXTUREPPM_H__

#include "LXTexture.h"

class LXTexturePPM : public LXTexture{
 public:    
  LXTexturePPM();
  ~LXTexturePPM();

  void initWithPath(const char *path);
 
 private:
  unsigned char* mallocStringWithPPMFile(const char* filename, int &width, int &height);
  GLuint loadTexture(const char *filename);
};

#endif
