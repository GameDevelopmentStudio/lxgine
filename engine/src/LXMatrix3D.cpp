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

double &LXMatrix3D::operator()(int i, int j) {
  return element(i, j);
}

const double &LXMatrix3D::operator()(int i, int j) const {
  return element(i, j);
}

double &LXMatrix3D::element(int i, int j) {
  return matrix[i << 2 | j];
}

const double &LXMatrix3D::element(int i, int j) const {
  return matrix[i << 2 | j];
}

void LXMatrix3D::setRow(int i, const LXPoint3D &p) {
  for (int j = 0; j < 4; j++)
    element(i, j) = p[j];
}

void LXMatrix3D::setColumn(int j, const LXPoint3D &p) {
  for (int i = 0; i < 4; i++)
    element(i, j) = p[i];
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
  double sin_a = sin(alpha);
  double cos_a = cos(alpha);
  out.matrix[0] = cos_a;  out.matrix[1] = 0;  out.matrix[2] = sin_a;  out.matrix[3] = 0;
  out.matrix[4] = 0;      out.matrix[5] = 1;  out.matrix[6] = 0;      out.matrix[7] = 0;
  out.matrix[8] = -sin_a; out.matrix[9] = 0;  out.matrix[10] = cos_a; out.matrix[11] = 0;
  out.matrix[12] = 0;     out.matrix[13] = 0; out.matrix[14] = 0;     out.matrix[15] = 1;
  return out;
}

LXMatrix3D matrixWithYRotation(double alpha) {
  LXMatrix3D out;
  double sin_a= sin(alpha);
  double cos_a= cos(alpha);
  out.matrix[0] = 1;   out.matrix[1] = 0;     out.matrix[2] = 0;      out.matrix[3] = 0;
  out.matrix[4] = 0;   out.matrix[5] = cos_a; out.matrix[6] = -sin_a; out.matrix[7] = 0;
  out.matrix[8] = 0;   out.matrix[9] = sin_a; out.matrix[10] = cos_a; out.matrix[11] = 0;
  out.matrix[12] = 0;  out.matrix[13] = 0;    out.matrix[14] = 0;     out.matrix[15] = 1;
  return out;
}

LXMatrix3D matrixWithZRotation(double alpha) {
  LXMatrix3D out;
  double sin_a= sin(alpha);
  double cos_a= cos(alpha);
  out.matrix[0] = cos_a;  out.matrix[1] = -sin_a; out.matrix[2] = 0;  out.matrix[3] = 0;
  out.matrix[4] = sin_a;  out.matrix[5] = cos_a;  out.matrix[6] = 0;  out.matrix[7] = 0;
  out.matrix[8] = 0;      out.matrix[9] = 0;      out.matrix[10] = 1; out.matrix[11] = 0;
  out.matrix[12] = 0;     out.matrix[13] = 0;     out.matrix[14] = 0; out.matrix[15] = 1;
  return out;
}


#pragma mark -(R3->R3)x(R3->R3)->(R3->R3) Functions

LXMatrix3D multiply(const LXMatrix3D &A, const LXMatrix3D &B) {
  // Save result in tmp matrix to avoid conflicts between A, B and this
  LXMatrix3D out;

  for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
          out(i, j) = 0;
          for (int k = 0; k < 4; k++) {
            out(i,j) += A(i, k) * B(k, j);
          }
      }
  }
  return out;
}

#pragma mark - (R3->R3)xR3->R3 Functions

LXPoint3D transformPoint(const LXMatrix3D &A, const LXPoint3D &p) {
  LXPoint3D out;
  for (int i = 0; i < 4; i++) {
    out[i] = 0;
    for (int j = 0; j < 4; j++) {
      out[i] += A(i,j) * p[j];
    }
  }
  return out;
}

