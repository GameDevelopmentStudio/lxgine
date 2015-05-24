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

    Vec4 computeNormal(Vec4 *vertexPool);
    Vec4 computeCenter(Vec4 *vertexPool);

private:
    int nextVertex(int idx);
};

#endif
