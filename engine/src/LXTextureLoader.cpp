#include "LXTextureLoader.h"

#include "LXUtils.h"
#include "LXTexturePPM.h"
#include "LXTextureTGA.h"

#include "stdio.h"

/* LXTextureLoader::LXTextureLoader() { */
/* } */
  
/* LXTextureLoader::~LXTextureLoader() { */

/* } */

LXTexture *LXTextureLoader::newTextureAtPath(const char *path) {
  LXTexture *out;
  char *extension = getFileExtension(path);
  if (strcmp(extension, "ppm") == 0) {
    out = new LXTexturePPM();
  } else if (strcmp(extension, "tga") == 0) {
    out = new LXTextureTGA();
  } else {
    return NULL;
  }

  out->initWithPath(path);
  return out;
}
