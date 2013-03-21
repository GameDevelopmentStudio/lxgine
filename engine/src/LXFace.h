#ifndef __LXFace_H__
#define __LXFace_H__

class LXPoint3D;

class LXFace {
 public:

  struct LXVertexNormalPair {
    int vertex;
    int normal;
  };

  int nvertex;
  LXVertexNormalPair *vertexNormals;
  
  LXFace();
  virtual ~LXFace();

  virtual void init(int nvertex);

  LXPoint3D *computeNormal(LXPoint3D *vertexPool);
  /* LXPoint3D *getCenter(); */
};

#endif
