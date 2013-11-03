#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Glut.h"

class Texture {
public:
    GLuint index; 
    
    Texture();
    virtual ~Texture();

    virtual void initWithPath(const char *path) = 0;
 
protected:
    virtual GLuint createTexture(GLenum target, int w, int h, void *data);
};

#endif
