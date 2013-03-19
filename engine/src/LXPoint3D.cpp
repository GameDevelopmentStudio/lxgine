#include "LXPoint3D.h"
#include "LXMatrix3D.h"
#include <math.h>

LXPoint3D::LXPoint3D(double x, double y, double z, int v) 
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->v = v;
}

LXPoint3D::~LXPoint3D() {}

#pragma mark - R->R Functions

double LXPoint3D::getCoord(int index) {
    switch (index) {
      case 0: return x;
      case 1: return y;
      case 2: return z;
      case 3: return v;
      default: return 0; // BAD PRACTICE MAN
    }
}

void LXPoint3D::setCoord(int index, double value) {
    switch (index) {
      case 0: x = value; break;
      case 1: y = value; break;
      case 2: z = value; break;
      case 3: v = value; break;
      default: break;
    }
}

#pragma mark - R3->R Functions

double LXPoint3D::module()
{
    return sqrt(scalarDot(this, this));
}

#pragma mark - R3->R3 Functions

void LXPoint3D::setValuesWithNormalizedVector(LXPoint3D *a) {
    double mod = a->module();
    x /= mod;
    y /= mod;
    z /= mod;
}

#pragma mark - R3xR3->R Functions

double scalarDot(LXPoint3D *a, LXPoint3D *b) {
    return a->x*b->x + a->y*b->y + a->z*b->z;
}

#pragma mark - R3xR3->R3 Functions

void LXPoint3D::setValuesWithSubstraction(LXPoint3D *a, LXPoint3D *b) {
    x = a->x - b->x;
    y = a->y - b->y;
    z = a->z - b->z;
    v = a->v - b->v;
}


void LXPoint3D::setValuesWithAddition(LXPoint3D *a, LXPoint3D *b) {
    x = a->x + b->x;
    y = a->y + b->y;
    z = a->z + b->z;
    v = a->v + b->v;
}

void LXPoint3D::setValuesWithCrossProduct(LXPoint3D *a, LXPoint3D *b) {
    // Avoid parameter modification during operations (self might be a or b)
    double ax, ay, az;
    ax = a->x; ay = a->y; az = a->z;
    double bx, by, bz;
    bx = b->x; by = b->y; bz = b->z;
    
    x = ay*bz - az*by;
    y = az*bx - ax*bz;
    z = ax*by - ay*bx;
    v = 0.0; // CHECK?
}

#pragma mark - (R3->R3)xR3->R3 Functions

// TODO:refactor
void LXPoint3D::setValuesWithTransformation(LXMatrix3D *matrix, LXPoint3D *point) {

  int i, j;
  double coord = 0;
  LXPoint3D tmp(x, y, z, v);
  for (int n = 0; n < 16; n++) {
    // TODO: maybe i & j as counters to avoid division?
    i = n / 4; 
    j = n % 4;

    coord += matrix->matrix[n] * tmp.getCoord(j);
    if (j == 3) {
      setCoord(i, coord);
      coord = 0;
    }
  }
}

