#ifndef __LXTEXTURE_H__
#define __LXTEXTURE_H__

#include "LXGlut.h"

class LXTexture {
 public:    
  GLuint index; 
  
  LXTexture();
  virtual ~LXTexture();

  virtual void initWithPath(const char *path) = 0;
 
 protected:
  virtual GLuint createTexture(GLenum target, int w, int h, void *data);
};

#endif
