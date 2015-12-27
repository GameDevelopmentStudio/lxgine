#include "Transform3D.h"

// Transformations
template<>
void Transform3D<float>::translate(float tx, float ty, float tz, bool premultiply) {
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(tx, ty, tz);
    Matrix44<float> transform;
    glGetFloatv(GL_MODELVIEW_MATRIX, transform.getAsArray());
    glPopMatrix();
    
    // Apply transform to one's matrix
    if (premultiply)
        matrix.load(transform * matrix);
    else
        matrix.load(matrix * transform);
}

template<>
void Transform3D<double>::translate(double tx, double ty, double tz, bool premultiply) {
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslated(tx, ty, tz);
    Matrix44<double> transform;
    glGetDoublev(GL_MODELVIEW_MATRIX, transform.getAsArray());
    glPopMatrix();
    
    // Apply transform to one's matrix
    if (premultiply)
        matrix.load(transform * matrix);
    else
        matrix.load(matrix * transform);
}

template<>
void Transform3D<float>::rotate(float rx, float ry, float rz, bool premultiply) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    if (rx != 0)
        glRotatef(rx, 1, 0, 0);
    if (ry != 0)
        glRotatef(ry, 0, 0, 1);
    if (rz != 0)
        glRotatef(rz, 0, 1, 0);
    Matrix44<float> transform;
    glGetFloatv(GL_MODELVIEW_MATRIX, transform.getAsArray());
    glPopMatrix();
    
    // Apply transform to one's matrix
    if (premultiply)
        matrix.load(transform * matrix);
    else
        matrix.load(matrix * transform);
}

template<>
void Transform3D<double>::rotate(double rx, double ry, double rz, bool premultiply) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    if (rx != 0)
        glRotated(rx, 1, 0, 0);
    if (ry != 0)
        glRotated(ry, 0, 0, 1);
    if (rz != 0)
        glRotated(rz, 0, 1, 0);
    Matrix44<double> transform;
    glGetDoublev(GL_MODELVIEW_MATRIX, transform.getAsArray());
    glPopMatrix();
    
    // Apply transform to one's matrix
    if (premultiply)
        matrix.load(transform * matrix);
    else
        matrix.load(matrix * transform);
}

// Apply changes
template<>
void Transform3D<float>::commit() {
    glMultMatrixf(matrix.getAsArray());
}

template<>
void Transform3D<double>::commit() {
    glMultMatrixd(matrix.getAsArray());
}