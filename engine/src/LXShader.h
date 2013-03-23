#ifndef __LXSHADER_H__
#define __LXSHADER_H__

#include "LXGlut.h"

class LXShader {
 public:
  LXShader();
  ~LXShader();

  void init(const char *vertPathName, 
            const char *fragPathName, 
            const char *geomPathName=NULL, 
            GLenum gsInput=GL_POINTS, 
            GLenum gsOutput=GL_TRIANGLE_STRIP);
  
  unsigned int programId();

  void enable();
  void disable();

  void setUniform1f(const char *name, float value);
  void setUniform2f(const char *name, float x, float y);
  void setUniform3f(const char *name, float x, float y, float z);
  void setUniform4f(const char *name, float x, float y, float z, float w);
  void setUniformfv(const char *name, float *v, int elementSize, int count=1);
  void setUniformMatrix4fv(const char *name, float *m, bool transpose);

  void bindTexture(const char *name, unsigned int tex, GLenum target, int unit);

 private:
  unsigned int id;

  void tearDown(unsigned int vertShader=0, unsigned int fragShader=0, unsigned int geomShader=0);
  bool checkCompileStatus(unsigned int shader);
  bool compileShader(const char *vertPathName, GLenum shaderType, unsigned int &shader);

  unsigned int compileProgram(const char *vertPathName, 
                              const char *fragPathName, 
                              const char *geomPathName,
                              GLenum gsInput=GL_POINTS, 
                              GLenum gsOutput=GL_TRIANGLE_STRIP);

};

#endif
