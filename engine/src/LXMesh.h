#ifndef __LXMesh_H__
#define __LXMesh_H__

#include "LXGlut.h"

class LXPoint3D;
class LXFace;

class LXMesh {
 public:
  // Uncompiled
  int nvertex;
  LXPoint3D *vertexPool;
  int nnormals;
  LXPoint3D *normalPool;
  int nfaces;
  LXFace *faces;

  // Compiled
  int compiledVertexCount;
  double *compiledVertex;

  LXMesh();
  virtual ~LXMesh();

  virtual void init(int nvertex, int nnormals);
  void computeNormals();
  void compile();

  virtual void render();
// private:
  GLuint vaoIdx[1];
  GLuint vboIdx[1];
};

#endif
