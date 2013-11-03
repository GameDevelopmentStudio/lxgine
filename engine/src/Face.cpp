#include "Face.h"

Face::Face() {

}

Face::~Face() {
    delete [] vertexNormalPairs;
}

void Face::init(int nvertex) {
    this->nvertex = nvertex;
    vertexNormalPairs = new VertexNormalPair[nvertex];
}

int Face::nextVertex(int idx) {
    return (idx + 1) % nvertex;
}

Point3D Face::computeNormal(Point3D *vertexPool) {
    
    Point3D out = Point3D(0, 0, 0, 0);
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

Point3D Face::computeCenter(Point3D *vertexPool) {
    // TODO: test
    Point3D center = Point3D(0, 0, 0, 1);
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
