#ifndef __Face_H__
#define __Face_H__

#include "Vector4.h"

class Face {
public:

    struct VertexNormalPair {
        int vertex;
        int normal;
    };

    int nvertex;
    VertexNormalPair *vertexNormalPairs;
    
    Face();
    virtual ~Face();

    virtual void init(int nvertex);

    Vector4f computeNormal(Vector4f *vertexPool);
    Vector4f computeCenter(Vector4f *vertexPool);

private:
    int nextVertex(int idx);
};

#endif
