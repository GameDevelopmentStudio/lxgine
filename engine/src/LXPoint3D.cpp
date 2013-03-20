#include "LXPoint3D.h"
#include "LXMatrix3D.h"
#include <math.h>

#include <iostream>

LXPoint3D::LXPoint3D(double x, double y, double z, int v) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->v = v;
}

LXPoint3D::LXPoint3D(const LXPoint3D &other) {
  x = other.x;
  y = other.y;
  z = other.z;
  v = other.v;
}

LXPoint3D::~LXPoint3D() {
}

#pragma mark - N->R Functions

double &LXPoint3D::operator[](int i) {
  return coords[i];
}

const double &LXPoint3D::operator[](int i) const {
  return coords[i];
}

#pragma mark - R3->R Functions

double LXPoint3D::module() const {
  return sqrt(scalarDot(*this, *this));
}

#pragma mark - R3->R3 Functions

LXPoint3D normalizedVector(const LXPoint3D &v) {
  double mod = v.module();
  return LXPoint3D(v.x / mod, 
                   v.y / mod, 
                   v.z / mod);
}

#pragma mark - R3xR3->R Functions

double scalarDot(const LXPoint3D &a, const LXPoint3D &b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

#pragma mark - R3xR3->R3 Functions

LXPoint3D operator-(const LXPoint3D &a, const LXPoint3D &b) {
  return LXPoint3D(a.x - b.x,
                   a.y - b.y,
                   a.z - b.z,
                   a.v - b.v);
}

LXPoint3D operator+(const LXPoint3D &a, const LXPoint3D &b) {
  return LXPoint3D(a.x + b.x,
                   a.y + b.y,
                   a.z + b.z,
                   a.v + b.v);
}

LXPoint3D crossProduct(const LXPoint3D &a, const LXPoint3D &b) {
  return LXPoint3D(a.y*b.z - a.z*b.y,
                   a.z*b.x - a.x*b.z,
                   a.x*b.y - a.y*b.x,
                   0.0); // CHECK?
}

