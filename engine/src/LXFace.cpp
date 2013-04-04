#include "LXFace.h"

LXFace::LXFace() {

}

LXFace::~LXFace() {
  delete [] vertexNormalPairs;
}

void LXFace::init(int nvertex) {
  this->nvertex = nvertex;
  vertexNormalPairs = new LXVertexNormalPair[nvertex];
}

int LXFace::nextVertex(int idx) {
  return (idx + 1) % nvertex;
}

LXPoint3D LXFace::computeNormal(LXPoint3D *vertexPool) {
  
  LXPoint3D out = LXPoint3D(0, 0, 0, 0);
  for (int i = 0; i < nvertex; i++) {
    // (yi - suc(yi))*(zi + suc(zi)
    out.x += (vertexPool[vertexNormalPairs[i].vertex].y - vertexPool[vertexNormalPairs[nextVertex(i)].vertex].y) *
          (vertexPool[vertexNormalPairs[i].vertex].z + vertexPool[vertexNormalPairs[nextVertex(i)].vertex].z);

    // (zi - suc(zi))*(xi + suc(xi)
    out.y += (vertexPool[vertexNormalPairs[i].vertex].z - vertexPool[vertexNormalPairs[nextVertex(i)].vertex].z) *
          (vertexPool[vertexNormalPairs[i].vertex].x + vertexPool[vertexNormalPairs[nextVertex(i)].vertex].x);

    // (xi - suc(xi))*(yi + suc(yi)
    out.z += (vertexPool[vertexNormalPairs[i].vertex].x - vertexPool[vertexNormalPairs[nextVertex(i)].vertex].x) *
          (vertexPool[vertexNormalPairs[i].vertex].y + vertexPool[vertexNormalPairs[nextVertex(i)].vertex].y);
  }
	return out;
}

LXPoint3D LXFace::computeCenter(LXPoint3D *vertexPool) {
  // TODO: test
  LXPoint3D center = LXPoint3D(0, 0, 0, 1);
  for (int i = 0; i < nvertex; i++) {
    center.x += vertexPool[vertexNormalPairs[i].vertex].x;
    center.y += vertexPool[vertexNormalPairs[i].vertex].y;
    center.z += vertexPool[vertexNormalPairs[i].vertex].z;
  }

  center.x /= (double) nvertex;
  center.y /= (double) nvertex;
  center.z /= (double) nvertex;
    
  return center;
}
