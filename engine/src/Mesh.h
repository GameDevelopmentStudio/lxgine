#ifndef __Mesh_H__
#define __Mesh_H__

#include "Glut.h"

class Vector3;
class Face;

class Mesh {
public:
    // Uncompiled
    int nvertex;
    Vector3 *vertexPool;
    int nnormals;
    Vector3 *normalPool;
    int nfaces;
    Face *faces;

    // Compiled
    int compiledVertexCount;
    double *compiledVertex;

    Mesh();
    virtual ~Mesh();

    virtual void init(int nvertex, int nnormals);
    void computeNormals();
    void compile();

    virtual void render();
private:
    GLuint vaoIdx[1];
    GLuint vboIdx[1];
};

#endif
