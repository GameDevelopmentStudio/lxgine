#include "TextureLoader.h"

#include "Utils.h"
#include "TexturePPM.h"
#include "TextureTGA.h"

#include <string>

Texture *TextureLoader::newTextureAtPath(const char *path) {
    Texture *out;
    std::string extension = getFileExtension(path);
    if (extension == "ppm") {
        out = new TexturePPM();
    } else if (extension == "tga") {
        out = new TextureTGA();
    } else {
        return NULL;
    }

    out->initWithPath(path);
    return out;
}
