#include "LXTextureLoader.h"

#include "LXUtils.h"
#include "LXTexturePPM.h"
#include "LXTextureTGA.h"

#include <string>

LXTexture *LXTextureLoader::newTextureAtPath(const char *path) {
  LXTexture *out;
  std::string extension = getFileExtension(path);
  if (extension == "ppm") {
    out = new LXTexturePPM();
  } else if (extension == "tga") {
    out = new LXTextureTGA();
  } else {
    return NULL;
  }

  out->initWithPath(path);
  return out;
}
