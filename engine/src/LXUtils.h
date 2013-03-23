#ifndef __UTILS_H__
#define __UTILS_H__

char *mallocStringWithContentsOfFile(const char *filename);
char *mallocStringWithEngineResource(const char *name, const char *extension);

#endif
