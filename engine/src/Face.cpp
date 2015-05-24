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

Vec4 Face::computeNormal(Vec4 *vertexPool) {
    
    Vec4 out = Vec4(0, 0, 0, 0);
    for (int i = 0; i < nvertex; i++) {
        // (yi - suc(yi))*(zi + suc(zi)
        out.getX() += (vertexPool[vertexNormalPairs[i].vertex].getY() - vertexPool[vertexNormalPairs[nextVertex(i)].vertex].getY()) *
                    (vertexPool[vertexNormalPairs[i].vertex].getZ() + vertexPool[vertexNormalPairs[nextVertex(i)].vertex].getZ());

        // (zi - suc(zi))*(xi + suc(xi)
        out.getY() += (vertexPool[vertexNormalPairs[i].vertex].getZ() - vertexPool[vertexNormalPairs[nextVertex(i)].vertex].getZ()) *
                    (vertexPool[vertexNormalPairs[i].vertex].getX() + vertexPool[vertexNormalPairs[nextVertex(i)].vertex].getX());

        // (xi - suc(xi))*(yi + suc(yi)
        out.getZ() += (vertexPool[vertexNormalPairs[i].vertex].getX() - vertexPool[vertexNormalPairs[nextVertex(i)].vertex].getX()) *
                    (vertexPool[vertexNormalPairs[i].vertex].getY() + vertexPool[vertexNormalPairs[nextVertex(i)].vertex].getY());
    }
    return out;
}

Vec4 Face::computeCenter(Vec4 *vertexPool) {
    // TODO: test
    Vec4 center = Vec4(0, 0, 0, 1);
    for (int i = 0; i < nvertex; i++) {
        center.getX() += vertexPool[vertexNormalPairs[i].vertex].getX();
        center.getY() += vertexPool[vertexNormalPairs[i].vertex].getY();
        center.getZ() += vertexPool[vertexNormalPairs[i].vertex].getZ();
    }

    center.getX() /= (float) nvertex;
    center.getY() /= (float) nvertex;
    center.getZ() /= (float) nvertex;
        
    return center;
}
