#include "LXMesh.h"
#include "LXFace.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

LXMesh::LXMesh() {
  nvertex = 0;
  nnormals = 0;
  nfaces = 0;
  vertexPool = NULL;
  normalPool = NULL;
  faces = NULL;

  compiledVertexCount = 0;
  compiledVertex = NULL;
}

LXMesh::~LXMesh() {
  if (vertexPool) delete []vertexPool;
  if (normalPool) delete []normalPool;
  if (faces) delete []faces;
  if (compiledVertex) delete []compiledVertex;
}

void LXMesh::init(int nvertex, int nnormals) {
  this->nvertex = nvertex;
  this->nnormals = nnormals;
  this->nfaces = nnormals;

  vertexPool = new LXPoint3D[nvertex];
  normalPool = new LXPoint3D[nnormals];
  faces = new LXFace[nfaces];
}

void LXMesh::computeNormals() {
  for (int i = 0; i < nfaces; i++) {
    normalPool[i] = faces[i].computeNormal(vertexPool);
    for (int j = 0; j < faces[i].nvertex; j++) {
      faces[i].vertexNormalPairs[j].normal = i;
    }
  }
}

void LXMesh::compile() {
  // TODO: revisit with more vertex info (color, texture...)

  compiledVertexCount = 0;
  for (int i = 0; i < nfaces; i++) {
    for (int j = 0; j < faces[i].nvertex; j++) {
      compiledVertexCount++;
    }
  }

  compiledVertex = new double[compiledVertexCount * 6]; // 3 vertex, 3 normal
  int n = 0;
  for (int i = 0; i < nfaces; i++) {
    for (int j = 0; j < faces[i].nvertex; j++) {
      int iV = faces[i].vertexNormalPairs[j].vertex;
      int iN = faces[i].vertexNormalPairs[j].normal;
      for (int k = 0; k < 3; k++) {
        compiledVertex[n + k] = vertexPool[iV][k];
        compiledVertex[n + k + 3] = normalPool[iN][k];
      }
      n += 6;
    }
  }
    
  glGenVertexArrays(1, &vaoIdx[0]);
  if (vaoIdx[0] != 0) {
    glBindVertexArray(vaoIdx[0]);
    
    glGenBuffers(1, &vboIdx[0]);
    if (vboIdx[0] != 0) {
      glBindBuffer(GL_ARRAY_BUFFER, vboIdx[0]);
      glBufferData(GL_ARRAY_BUFFER, compiledVertexCount * 6 * sizeof(double), compiledVertex, GL_DYNAMIC_DRAW);
        
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(3, GL_DOUBLE, 6 * sizeof(double), BUFFER_OFFSET(0));   //The starting point of the VBO, for the vertices
      glEnableClientState(GL_NORMAL_ARRAY);
      glNormalPointer(GL_DOUBLE, 6 * sizeof(double), BUFFER_OFFSET(3 * sizeof(double)));   //The starting point of normals

      // Don't need this anymore
      delete compiledVertex;
      compiledVertex = NULL;
      compiledVertexCount = 0;
    }
    glBindVertexArray(0);
  }
}

void LXMesh::render() {

  if (vaoIdx != 0 && vaoIdx[0] != 0) {
    glBindVertexArray(vaoIdx[0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
  } else if (compiledVertex) {
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glNormalPointer(GL_DOUBLE, 6 * sizeof(double), compiledVertex + 3);
    glVertexPointer(3, GL_DOUBLE, 6 * sizeof(double), compiledVertex);
    glDrawArrays(GL_TRIANGLES, 0, compiledVertexCount);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);    
  } else {
    for (int i = 0; i < nfaces; i++) {

      // TODO: textures here
      
      glBegin(GL_POLYGON);
      for (int j = 0; j < faces[i].nvertex; j++) {
        int iV = faces[i].vertexNormalPairs[j].vertex;
        int iN = faces[i].vertexNormalPairs[j].normal;
        glNormal3d(normalPool[iN].x, normalPool[iN].y, normalPool[iN].z);
        glVertex3d(vertexPool[iV].x, vertexPool[iV].y, vertexPool[iV].z);
      }
      glEnd();
    }
  }
}
