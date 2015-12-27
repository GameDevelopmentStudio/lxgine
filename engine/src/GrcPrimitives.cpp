#include "GrcPrimitives.h"
#include "Glut.h"
#include "Vector.h"

template <> void GrcPrimitives::segment<float>(const Vector3<float>& vStart, const Vector3<float>& vEnd, Col color) {
    glBegin(GL_LINES);
        glColor4f(color.getRf(), color.getGf(), color.getBf(), color.getAf());
        glVertex3f(vStart.getX(), vStart.getY(), vStart.getZ());
        glVertex3f(vEnd.getX(), vEnd.getY(), vEnd.getZ());
    glEnd();
}

template <> void GrcPrimitives::segment<double>(const Vector3<double>& vStart, const Vector3<double>& vEnd, Col color) {
    glBegin(GL_LINES);
        glColor4f(color.getRf(), color.getGf(), color.getBf(), color.getAf());
        glVertex3d(vStart.getX(), vStart.getY(), vStart.getZ());
        glVertex3d(vEnd.getX(), vEnd.getY(), vEnd.getZ());
    glEnd();
}