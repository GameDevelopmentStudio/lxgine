#ifndef __Face_H__
#define __Face_H__

#include "Vector3.h"

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

    Vector3 computeNormal(Vector3 *vertexPool);
    Vector3 computeCenter(Vector3 *vertexPool);

private:
    int nextVertex(int idx);
};

#endif
