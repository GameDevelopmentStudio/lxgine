#include "LXFace.h"
#include "LXPoint3D.h"

LXFace::LXFace() {

}

LXFace::~LXFace() {
  delete [] vertexNormals;
}

void LXFace::init(int nvertex) {
  this->nvertex = nvertex;
  vertexNormals = new LXVertexNormalPair[nvertex]();
}

LXPoint3D *LXFace::computeNormal(LXPoint3D *vertexPool) {

}
