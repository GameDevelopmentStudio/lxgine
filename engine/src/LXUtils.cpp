#include "LXUtils.h"

#include <fstream>
#include <stdlib.h>
#include <string.h>

char *mallocStringWithContentsOfFile(const char *filename) {
  std::ifstream in(filename, std::ios::in);
  if (in) {
    // Get file length and prepare buffer
    in.seekg(0, std::ios::end);
    int dataLength = in.tellg();
    char *data = (char *)malloc(dataLength);
    // Start reading
    in.seekg(0, std::ios::beg);
    in.read(data, dataLength);
    in.close();
    return data;
  } else {
    return NULL;
  }
}

char *mallocStringWithEngineResource(const char *name, const char *extension) {
  char *result = (char *) malloc((strlen(name) + strlen(extension) + 2) * sizeof(char));
  // Create mutale copy of the name
  strcpy(result, name);
  // Append extension
  strcat(result, extension);
  return result;
}


char *getFileExtension(const char *filename) {
  // TODO: tmp implementation, better use ext library (boost)
  std::string strPath = std::string(filename);
  std::string extension = strPath.substr(strPath.find_last_of(".") + 1);

  return &extension[0];
}

