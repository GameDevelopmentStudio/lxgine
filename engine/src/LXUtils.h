#ifndef __UTILS_H__
#define __UTILS_H__

char *callocStringWithContentsOfFile(const char *filename);
char *callocStringWithEngineResource(const char *name, const char *extension);
char *getFileExtension(const char *filename);

#endif
