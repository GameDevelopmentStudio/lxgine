#include "Mesh.h"
#include "Face.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

Mesh::Mesh() {
    nvertex = 0;
    nnormals = 0;
    nfaces = 0;
    vertexPool = NULL;
    normalPool = NULL;
    faces = NULL;

    compiledVertexCount = 0;
    compiledVertex = NULL;
        
    vaoIdx[0] = vboIdx[0] = 0;
}

Mesh::~Mesh() {
    if (vertexPool) delete []vertexPool;
    if (normalPool) delete []normalPool;
    if (faces) delete []faces;
    if (compiledVertex) delete []compiledVertex;
    if (vboIdx[0] > 0) {
        glDeleteBuffers(1, vboIdx);
    }
    if (vaoIdx[0] > 0) {
        glDeleteVertexArrays(1, vaoIdx);
    }
}

void Mesh::init(int nvertex, int nnormals) {
    this->nvertex = nvertex;
    this->nnormals = nnormals;
    this->nfaces = nnormals;

    vertexPool = new Vector4f[nvertex];
    normalPool = new Vector4f[nnormals];
    faces = new Face[nfaces];
}

void Mesh::computeNormals() {
    for (int i = 0; i < nfaces; i++) {
        normalPool[i] = faces[i].computeNormal(vertexPool);
        for (int j = 0; j < faces[i].nvertex; j++) {
            faces[i].vertexNormalPairs[j].normal = i;
        }
    }
}

void Mesh::compile() {
    // TODO: revisit with more vertex info (color, texture...)

    compiledVertexCount = 0;
    for (int i = 0; i < nfaces; i++) {
        for (int j = 0; j < faces[i].nvertex; j++) {
            compiledVertexCount++;
        }
    }

    compiledVertex = new float[compiledVertexCount * 6]; // 3 vertex, 3 normal
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
    
    glGenVertexArrays(1, vaoIdx);
    if (vaoIdx[0] != 0) {
        glBindVertexArray(vaoIdx[0]);
        
        glGenBuffers(1, vboIdx);
        if (vboIdx[0] != 0) {
            glBindBuffer(GL_ARRAY_BUFFER, vboIdx[0]);
            glBufferData(GL_ARRAY_BUFFER, compiledVertexCount * 6 * sizeof(float), compiledVertex, GL_STATIC_DRAW);

            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_NORMAL_ARRAY);
            glVertexPointer(3, GL_FLOAT, 6 * sizeof(float), BUFFER_OFFSET(0));     //The starting point of the VBO, for the vertices
            glNormalPointer(GL_FLOAT, 6 * sizeof(float), BUFFER_OFFSET(3 * sizeof(float)));     //The starting point of normals
            glDisableClientState(GL_NORMAL_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Don't need this anymore
            delete compiledVertex;
            compiledVertex = NULL;
        }
        glBindVertexArray(0);
    }
}

void Mesh::render() {

    if (vaoIdx[0] > 0 && vboIdx[0] > 0) {
        glBindVertexArray(vaoIdx[0]);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);

        glDrawArrays(GL_TRIANGLES, 0, compiledVertexCount);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glBindVertexArray(0);
    } else if (compiledVertex) {
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        
        glNormalPointer(GL_FLOAT, 6 * sizeof(float), compiledVertex + 3);
        glVertexPointer(3, GL_FLOAT, 6 * sizeof(float), compiledVertex);
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
                glNormal3f(normalPool[iN].x, normalPool[iN].y, normalPool[iN].z);
                glVertex3f(vertexPool[iV].x, vertexPool[iV].y, vertexPool[iV].z);
            }
            glEnd();
        }
    }
}
