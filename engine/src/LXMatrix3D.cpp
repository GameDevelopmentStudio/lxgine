#include "LXMatrix3D.h"
#include <math.h>

#include "LXGlut.h"

LXMatrix3D::LXMatrix3D() {

}

LXMatrix3D::~LXMatrix3D() {
    /* delete []matrix; */
}

void LXMatrix3D::init() {
    matrix[0] = 1;  matrix[1] = 0;  matrix[2] = 0;  matrix[3] = 0;
    matrix[4] = 0;  matrix[5] = 1;  matrix[6] = 0;  matrix[7] = 0;
    matrix[8] = 0;  matrix[9] = 0;  matrix[10] = 1; matrix[11] = 0;
    matrix[12] = 0; matrix[13] = 0; matrix[14] = 0; matrix[15] = 1;
}

double LXMatrix3D::get(int i, int j) {
    return matrix[i*4 + j];
}

double LXMatrix3D::set(int i, int j, double value) {
    matrix[i*4 + j] = value;
}

void LXMatrix3D::setRow(int i, LXPoint3D *p) {
    set(i, 0, p->x);
    set(i, 1, p->y);
    set(i, 2, p->z);
    set(i, 3, p->v);
}

void LXMatrix3D::setColumn(int j, LXPoint3D *p) {
    set(0, j, p->x);
    set(1, j, p->y);
    set(2, j, p->z);
    set(3, j, p->v);
}

void LXMatrix3D::setValuesWithMultiplication(LXMatrix3D* A, LXMatrix3D* B) {

    // Save result in tmp matrix to avoid conflicts between A, B and this
    LXMatrix3D tmp;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            double cell = 0;
            for (int k = 0; k < 4; k++) {
              cell += A->get(i, k) * B->get(k, j);
            }
            tmp.set(i, j, cell);
        }
    }

    for (int n = 0; n < 16; n++) {
      matrix[n] = tmp.matrix[n];
    }
}

void LXMatrix3D::setValuesWithXRotation(double alpha) {
    matrix[0] = cos(alpha);   matrix[1] = 0;  matrix[2] = sin(alpha);   matrix[3] = 0;
    matrix[4] = 0;            matrix[5] = 1;  matrix[6] = 0;            matrix[7] = 0;
    matrix[8] = -sin(alpha);  matrix[9] = 0;  matrix[10] = cos(alpha);  matrix[11] = 0;
    matrix[12] = 0;           matrix[13] = 0; matrix[14] = 0;           matrix[15] = 1;
}

void LXMatrix3D::setValuesWithYRotation(double alpha) {
    matrix[0] = 1;   matrix[1] = 0;           matrix[2] = 0;             matrix[3] = 0;
    matrix[4] = 0;   matrix[5] = cos(alpha);  matrix[6] = -sin(alpha);  matrix[7] = 0;
    matrix[8] = 0;   matrix[9] = sin(alpha);  matrix[10] = cos(alpha);  matrix[11] = 0;
    matrix[12] = 0;  matrix[13] = 0;          matrix[14] = 0;           matrix[15] = 1;
}

void LXMatrix3D::setValuesWithZRotation(double alpha) {
    matrix[0] = cos(alpha);   matrix[1] = -sin(alpha);  matrix[2] = 0;  matrix[3] = 0;
    matrix[4] = sin(alpha);   matrix[5] = cos(alpha);   matrix[6] = 0;  matrix[7] = 0;
    matrix[8] = 0;            matrix[9] = 0;            matrix[10] = 1; matrix[11] = 0;
    matrix[12] = 0;           matrix[13] = 0;           matrix[14] = 0; matrix[15] = 1;
}

#pragma mark - Transformations

// Transformations
void LXMatrix3D::translate(double tx, double ty, double tz) {
  
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        glTranslated(tx, ty, tz);
        LXMatrix3D transform;
        glGetDoublev(GL_MODELVIEW_MATRIX, transform.matrix);
    glPopMatrix();

    // Apply transform to one's matrix
    setValuesWithMultiplication(this, &transform);
}

void LXMatrix3D::rotate(double rx, double ry, double rz) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        if (rx != 0)
            glRotated(rx, 1, 0, 0);
          if (ry != 0)
            glRotated(ry, 0, 0, 1);
        if (rz != 0)
            glRotated(rz, 0, 1, 0);
        LXMatrix3D transform;
        glGetDoublev(GL_MODELVIEW_MATRIX, transform.matrix);
    glPopMatrix();

    // Apply transform to one's matrix
    setValuesWithMultiplication(this, &transform);
}

void LXMatrix3D::commit() {
    glMultMatrixd(matrix);
}
