#ifndef __TEXTURELOADER_H__
#define __TEXTURELOADER_H__

#include "Texture.h"

class TextureLoader    {
public:        
    static Texture *newTextureAtPath(const char *path);
};

#endif
