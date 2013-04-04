#ifndef __LXFace_H__
#define __LXFace_H__

#include "LXPoint3D.h"

class LXFace {
 public:

  struct LXVertexNormalPair {
    int vertex;
    int normal;
  };

  int nvertex;
  LXVertexNormalPair *vertexNormalPairs;
  
  LXFace();
  virtual ~LXFace();

  virtual void init(int nvertex);

  LXPoint3D computeNormal(LXPoint3D *vertexPool);
  LXPoint3D computeCenter(LXPoint3D *vertexPool);

 private:
  int nextVertex(int idx);
};

#endif
