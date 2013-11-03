#include "Point3D.h"
#include "Matrix3D.h"
#include <math.h>

#include <iostream>

Point3D::Point3D(double x, double y, double z, int v) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->v = v;
}

Point3D::Point3D(const Point3D &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    v = other.v;
}

Point3D::~Point3D() {
}

#pragma mark - N->R Functions

double &Point3D::operator[](int i) {
    return coords[i];
}

const double &Point3D::operator[](int i) const {
    return coords[i];
}

#pragma mark - R3->R Functions

double Point3D::module() const {
    return sqrt(scalarDot(*this, *this));
}

#pragma mark - R3->R3 Functions

Point3D Point3D::operator-() const {
    return Point3D(-x, -y, -v, -z);
}

Point3D normalizedVector(const Point3D &v) {
    double mod = v.module();
    return Point3D(v.x / mod, 
                                     v.y / mod, 
                                     v.z / mod,
                                     v.v / mod);
}

#pragma mark - RxR3->R3 Functions

Point3D operator*(const float &a, const Point3D &v) {
    return Point3D(a * v.x,
                                     a * v.y,
                                     a * v.z,
                                     a * v.v);
}

Point3D operator*(const Point3D &v, const float &a) {
    return Point3D(v.x * a,
                                     v.y * a,
                                     v.z * a,
                                     v.v * a);
}

#pragma mark - R3xR3->R Functions

double scalarDot(const Point3D &a, const Point3D &b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

#pragma mark - R3xR3->R3 Functions

Point3D operator-(const Point3D &a, const Point3D &b) {
    return Point3D(a.x - b.x,
                                     a.y - b.y,
                                     a.z - b.z,
                                     a.v - b.v);
}

Point3D operator+(const Point3D &a, const Point3D &b) {
    return Point3D(a.x + b.x,
                                     a.y + b.y,
                                     a.z + b.z,
                                     a.v + b.v);
}

void Point3D::operator-=(const Point3D &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    v -= other.v;
}

void Point3D::operator+=(const Point3D &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    v += other.v;
}

Point3D crossProduct(const Point3D &a, const Point3D &b) {
    return Point3D(a.y*b.z - a.z*b.y,
                                     a.z*b.x - a.x*b.z,
                                     a.x*b.y - a.y*b.x,
                                     0.0); // CHECK?
}

