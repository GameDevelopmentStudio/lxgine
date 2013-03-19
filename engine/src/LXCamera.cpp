#include "LXCamera.h"
#include "LXMatrix3D.h"
#include <math.h>

LXCamera::LXCamera() {
  eye = new LXPoint3D();
  look = new LXPoint3D();
  up = new LXPoint3D();
}

LXCamera::~LXCamera() {
  delete eye;
  delete look;
  delete up;
}

void LXCamera::init() {
  eye->x = 100.0; eye->y = 100.0; 
  eye->z = 100.0; eye->v = 1;
  look->x = 0.0; look->y = 0.0; 
  look->z = 0.0; look->v = 1;
  up->x = 0; up->y = 1; 
  up->z = 0; up->v = 0;

  viewVolume.N = 2;
  viewVolume.F = 10000;
  viewVolume.xR = 0.2;
  viewVolume.xL = -viewVolume.xR;
  viewVolume.yT = 0.2;
  viewVolume.yB = -viewVolume.yT;
}

void LXCamera::translate(double x, double y, double z) {

  LXPoint3D *trans = new LXPoint3D(x, y, z, 0.0);

  // first we get camera.eye system of coordinates
  LXPoint3D *n = new LXPoint3D();
  LXPoint3D *u = new LXPoint3D();
  LXPoint3D *v = new LXPoint3D();

  n->setValuesWithSubstraction(eye, look);
  n->setValuesWithNormalizedVector(n);

  u->setValuesWithCrossProduct(up, n);
  v->setValuesWithCrossProduct(n, u);

  // then we transform it (resulting matrix is kinda simple
  // so let's put the multiplication output here
  // notice how no eye vars appear here, that's because
  // desp is a vector and so desp->v is 0
  LXPoint3D *desp = new LXPoint3D(u->x*trans->x + v->x*trans->y + n->x*trans->z,
                                  u->y*trans->x + v->y*trans->y + n->y*trans->z,
                                  u->z*trans->x + v->z*trans->y + n->z*trans->z,
                                  0);

  eye->setValuesWithAddition(eye, desp);
  look->setValuesWithAddition(look, desp);

  delete desp;
  delete v;
  delete u;
  delete n;
  delete trans;
}

void LXCamera::translateX(double x) {
  translate(x, 0.0, 0.0);
}

void LXCamera::translateY(double y) {
  translate(0.0, y, 0.0);
}

void LXCamera::translateZ(double z) {
  translate(0.0, 0.0, z);
}

void LXCamera::rotate(double dx, double dy, double dz) {
  // lots of shit going on here
  // basically: a series of transformations are done here
  //  - transform camera.look into camera.eye's system of coordinates
  //  - rotate transformed camera.look horizontally and vertically, so
  //    that it moves a distance equal to dx on x and dy on y (talking in
  //    camera.eye system of coordinates)
  //  - return transformed and rotated camera.look to global coordinates.
  LXPoint3D *n = new LXPoint3D();
  LXPoint3D *u = new LXPoint3D();
  LXPoint3D *v = new LXPoint3D();

  LXMatrix3D *t1 = new LXMatrix3D();
  LXMatrix3D *t2 = new LXMatrix3D();
  LXMatrix3D *rotatex = new LXMatrix3D();
  LXMatrix3D *rotatey = new LXMatrix3D();
  LXMatrix3D *rotatez = new LXMatrix3D();

  LXMatrix3D *trasrot = new LXMatrix3D();
  LXMatrix3D *rotate = new LXMatrix3D();
  LXMatrix3D *matrix = new LXMatrix3D();

  n->setValuesWithSubstraction(eye, look);
  double r = n->module();
  n->setValuesWithNormalizedVector(n);
  u->setValuesWithCrossProduct(up, n);
  v->setValuesWithCrossProduct(n, u);

  double halpha = asin((dx/2.f)/r);
  double valpha = asin((dy/2.f)/r);
  double zalpha = asin((dz/2.f)/r);

  t1->matrix[0] = u->x; t1->matrix[1] = u->y; t1->matrix[2] = u->z;   t1->matrix[3] = -scalarDot(eye, u);
  t1->matrix[4] = v->x; t1->matrix[5] = v->y; t1->matrix[6] = v->z;   t1->matrix[7] = -scalarDot(eye, v);
  t1->matrix[8] = n->x; t1->matrix[9] = n->y; t1->matrix[10] = n->z;  t1->matrix[11] = -scalarDot(eye, n);
  t1->matrix[12] = 0;   t1->matrix[13] = 0;   t1->matrix[14] = 0;   t1->matrix[15] = 1;

  t2->matrix[0] = u->x; t2->matrix[1] = v->x; t2->matrix[2] = n->x;   t2->matrix[3] = eye->x;
  t2->matrix[4] = u->y; t2->matrix[5] = v->y; t2->matrix[6] = n->y;   t2->matrix[7] = eye->y;
  t2->matrix[8] = u->z; t2->matrix[9] = v->z; t2->matrix[10] = n->z;  t2->matrix[11] = eye->z;
  t2->matrix[12] = 0;   t2->matrix[13] = 0;   t2->matrix[14] = 0;   t2->matrix[15] = 1;
  
  rotatex->setValuesWithXRotation(halpha);
  rotatey->setValuesWithYRotation(valpha);
  // TODO: z rotation changes up vector
  /* rotatez->setValuesWithZRotation(zalpha); */

  rotate->setValuesWithMultiplication(rotatex, rotatey);
  /* rotate->setValuesWithMultiplication(rotate, rotatez); */
  trasrot->setValuesWithMultiplication(t2, rotate);
  matrix->setValuesWithMultiplication(trasrot, t1);

  look->setValuesWithTransformation(matrix, look);

  delete matrix;
  delete rotate;
  delete trasrot;
  delete rotatez;
  delete rotatey;
  delete rotatex;
  delete t2;
  delete t1;

  delete v;
  delete u;
  delete n;
}

void LXCamera::orbitate(double dx, double dy, double dz) {
  // lots of shit going on here
  // basically: a series of transformations are done here
  //    - transform camera.eye into camera.look's system of coordinates
  //    - rotate transformed camera.eye horizontally and vertically, so
  //      that it moves a distance equal to dx on x and dy on y (talking in
  //      camera.look system of coordinates)
  //    - return transformed and rotated camera.eye to global coordinates.

  LXPoint3D *n = new LXPoint3D();
  LXPoint3D *u = new LXPoint3D();
  LXPoint3D *v = new LXPoint3D();

  LXMatrix3D *t1 = new LXMatrix3D();
  LXMatrix3D *t2 = new LXMatrix3D();
  LXMatrix3D *rotatex = new LXMatrix3D();
  LXMatrix3D *rotatey = new LXMatrix3D();
  LXMatrix3D *rotatez = new LXMatrix3D();

  LXMatrix3D *trasrot = new LXMatrix3D();
  LXMatrix3D *rotate = new LXMatrix3D();
  LXMatrix3D *matrix = new LXMatrix3D();

  n->setValuesWithSubstraction(eye, look);
  double r = n->module();
  n->setValuesWithNormalizedVector(n);
  u->setValuesWithCrossProduct(up, n);
  v->setValuesWithCrossProduct(n, u);

  double halpha = asin((dx/2.f)/r);
  double valpha = asin((dy/2.f)/r);
  double zalpha = asin((dz/2.f)/r);

  t1->matrix[0] = u->x; t1->matrix[1] = u->y; t1->matrix[2] = u->z;   t1->matrix[3] = -scalarDot(look, u);
  t1->matrix[4] = v->x; t1->matrix[5] = v->y; t1->matrix[6] = v->z;   t1->matrix[7] = -scalarDot(look, v);
  t1->matrix[8] = n->x; t1->matrix[9] = n->y; t1->matrix[10] = n->z;  t1->matrix[11] = -scalarDot(look, n);
  t1->matrix[12] = 0;   t1->matrix[13] = 0;   t1->matrix[14] = 0;   t1->matrix[15] = 1;

  t2->matrix[0] = u->x; t2->matrix[1] = v->x; t2->matrix[2] = n->x;   t2->matrix[3] = look->x;
  t2->matrix[4] = u->y; t2->matrix[5] = v->y; t2->matrix[6] = n->y;   t2->matrix[7] = look->y;
  t2->matrix[8] = u->z; t2->matrix[9] = v->z; t2->matrix[10] = n->z;  t2->matrix[11] = look->z;
  t2->matrix[12] = 0;   t2->matrix[13] = 0;   t2->matrix[14] = 0;   t2->matrix[15] = 1;
  
  rotatex->setValuesWithXRotation(halpha);
  rotatey->setValuesWithYRotation(valpha);
  // TODO: z rotation changes up vector
  /* rotatez->setValuesWithZRotation(zalpha); */

  rotate->setValuesWithMultiplication(rotatex, rotatey);
  /* rotate->setValuesWithMultiplication(rotatez, rotate); */
  trasrot->setValuesWithMultiplication(t2, rotate);
  matrix->setValuesWithMultiplication(trasrot, t1);

  eye->setValuesWithTransformation(matrix, eye);

  delete matrix;
  delete rotate;
  delete trasrot;
  delete rotatez;
  delete rotatey;
  delete rotatex;
  delete t2;
  delete t1;

  delete v;
  delete u;
  delete n;
}
