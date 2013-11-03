#ifndef __TEXTUREPPM_H__
#define __TEXTUREPPM_H__

#include "Texture.h"

class TexturePPM : public Texture {
public:
    TexturePPM();
    ~TexturePPM();

    void initWithPath(const char *path);
 
private:
    unsigned char* mallocStringWithPPMFile(const char* filename, int &width, int &height);
    GLuint loadTexture(const char *filename);
};

#endif
