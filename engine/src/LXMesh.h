#ifndef __LXMesh_H__
#define __LXMesh_H__

class LXPoint3D;
class LXFace;

class LXMesh {
 public:
  int nvertex;
  LXPoint3D *vertex;
  int nnormals;
  LXPoint3D *normals;
  int nfaces;
  LXFace *faces;

  LXMesh();
  virtual ~LXMesh();

  virtual void init(int nvertex, int nnormals);
  void computeNormals();

  virtual void render();
};

#endif
