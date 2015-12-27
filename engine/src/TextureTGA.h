#ifndef __TEXTURETGA_H__
#define __TEXTURETGA_H__

#include "Texture.h"

class TextureTGA : public Texture {
public:
    TextureTGA();
    ~TextureTGA();

    void initWithPath(const char *path);
 
private:
    unsigned char* newStringWithTGAFile(const char* filename, int &width, int &height);
};

#endif
