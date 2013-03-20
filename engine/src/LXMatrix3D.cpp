#include "LXMatrix3D.h"
#include <math.h>

#include "LXGlut.h"
#include "LXPoint3D.h"

LXMatrix3D::LXMatrix3D() {

}

LXMatrix3D::LXMatrix3D(const LXMatrix3D &other) {
  for (int n = 0; n < 16; n++) {
    matrix[n] = other.matrix[n];
  }
}

LXMatrix3D::~LXMatrix3D() {
}

void LXMatrix3D::init() {
  matrix[0] = 1;  matrix[1] = 0;  matrix[2] = 0;  matrix[3] = 0;
  matrix[4] = 0;  matrix[5] = 1;  matrix[6] = 0;  matrix[7] = 0;
  matrix[8] = 0;  matrix[9] = 0;  matrix[10] = 1; matrix[11] = 0;
  matrix[12] = 0; matrix[13] = 0; matrix[14] = 0; matrix[15] = 1;
}

double LXMatrix3D::get(int i, int j) const {
  return matrix[i << 2 | j];
}

double LXMatrix3D::set(int i, int j, double value) {
  matrix[i << 2 | j] = value;
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
  *this = multiply(*this, transform);
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
  *this = multiply(*this, transform);
}

void LXMatrix3D::commit() {
    glMultMatrixd(matrix);
}

#pragma mark - Rotations

LXMatrix3D matrixWithXRotation(double alpha) {
  LXMatrix3D out;
  out.matrix[0] = cos(alpha);   out.matrix[1] = 0;  out.matrix[2] = sin(alpha);   out.matrix[3] = 0;
  out.matrix[4] = 0;            out.matrix[5] = 1;  out.matrix[6] = 0;            out.matrix[7] = 0;
  out.matrix[8] = -sin(alpha);  out.matrix[9] = 0;  out.matrix[10] = cos(alpha);  out.matrix[11] = 0;
  out.matrix[12] = 0;           out.matrix[13] = 0; out.matrix[14] = 0;           out.matrix[15] = 1;
  return out;
}

LXMatrix3D matrixWithYRotation(double alpha) {
  LXMatrix3D out;
  out.matrix[0] = 1;   out.matrix[1] = 0;           out.matrix[2] = 0;             out.matrix[3] = 0;
  out.matrix[4] = 0;   out.matrix[5] = cos(alpha);  out.matrix[6] = -sin(alpha);  out.matrix[7] = 0;
  out.matrix[8] = 0;   out.matrix[9] = sin(alpha);  out.matrix[10] = cos(alpha);  out.matrix[11] = 0;
  out.matrix[12] = 0;  out.matrix[13] = 0;          out.matrix[14] = 0;           out.matrix[15] = 1;
  return out;
}

LXMatrix3D matrixWithZRotation(double alpha) {
  LXMatrix3D out;
  out.matrix[0] = cos(alpha);   out.matrix[1] = -sin(alpha);  out.matrix[2] = 0;  out.matrix[3] = 0;
  out.matrix[4] = sin(alpha);   out.matrix[5] = cos(alpha);   out.matrix[6] = 0;  out.matrix[7] = 0;
  out.matrix[8] = 0;            out.matrix[9] = 0;            out.matrix[10] = 1; out.matrix[11] = 0;
  out.matrix[12] = 0;           out.matrix[13] = 0;           out.matrix[14] = 0; out.matrix[15] = 1;
  return out;
}

#pragma mark -(R3->R3)x(R3->R3)->(R3->R3) Functions

LXMatrix3D multiply(const LXMatrix3D &A, const LXMatrix3D &B) {
  // Save result in tmp matrix to avoid conflicts between A, B and this
  LXMatrix3D out;

  for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
          double cell = 0;
          for (int k = 0; k < 4; k++) {
            cell += A.get(i, k) * B.get(k, j);
          }
          out.set(i, j, cell);
      }
  }
  return out;
}

#pragma mark - (R3->R3)xR3->R3 Functions

// TODO:refactor
LXPoint3D transformPoint(const LXMatrix3D &A, const LXPoint3D &p) {
  int i, j;
  double coord = 0;
  LXPoint3D out;
  for (int n = 0; n < 16; n++) {
    i = n >> 2; 
    j = n & 3;

    coord += A.matrix[n] * p.getCoord(j);
    if (j == 3) {
      out.setCoord(i, coord);
      coord = 0;
    }
  }
  return out;
}

