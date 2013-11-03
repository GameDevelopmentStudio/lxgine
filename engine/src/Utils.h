#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <string.h>
#include <fstream>

char *callocStringWithContentsOfFile(const char *filename);
char *callocStringWithEngineResource(const char *name, const char *extension);
std::string getFileExtension(const char *filename);

#endif
