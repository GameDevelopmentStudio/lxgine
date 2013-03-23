#ifndef __LXTEXTURELOADER_H__
#define __LXTEXTURELOADER_H__

#include "LXTexture.h"

class LXTextureLoader  {
 public:    
  static LXTexture *newTextureAtPath(const char *path);
};

#endif
