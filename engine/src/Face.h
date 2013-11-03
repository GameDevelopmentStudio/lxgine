#ifndef __Face_H__
#define __Face_H__

#include "Point3D.h"

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

    Point3D computeNormal(Point3D *vertexPool);
    Point3D computeCenter(Point3D *vertexPool);

private:
    int nextVertex(int idx);
};

#endif
