#ifndef __Mesh_H__
#define __Mesh_H__

#include "Glut.h"
#include "Vector.h"

class Face;

class Mesh {
public:
    // Uncompiled
    int nvertex;
    Vector4f *vertexPool;
    int nnormals;
    Vector4f *normalPool;
    int nfaces;
    Face *faces;

    // Compiled
    int compiledVertexCount;
    float *compiledVertex;

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