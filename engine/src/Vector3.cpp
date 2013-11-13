#include "Vector3.h"
#include "Matrix3D.h"
#include <math.h>

#include <iostream>

Vector3::Vector3(double x, double y, double z, int v) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->v = v;
}

Vector3::Vector3(const Vector3 &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    v = other.v;
}

Vector3::~Vector3() {
}

#pragma mark - N->R Functions

double &Vector3::operator[](int i) {
    return coords[i];
}

const double &Vector3::operator[](int i) const {
    return coords[i];
}

#pragma mark - R3->R Functions

double Vector3::module() const {
    return sqrt(scalarDot(*this, *this));
}

#pragma mark - R3->R3 Functions

Vector3 Vector3::operator-() const {
    return Vector3(-x, -y, -v, -z);
}

Vector3 normalizedVector(const Vector3 &v) {
    double mod = v.module();
    return Vector3(v.x / mod,
                   v.y / mod,
                   v.z / mod,
                   v.v / mod);
}

#pragma mark - RxR3->R3 Functions

Vector3 operator*(const float &a, const Vector3 &v) {
    return Vector3(a * v.x,
                   a * v.y,
                   a * v.z,
                   a * v.v);
}

Vector3 operator*(const Vector3 &v, const float &a) {
    return Vector3(v.x * a,
                   v.y * a,
                   v.z * a,
                   v.v * a);
}

#pragma mark - R3xR3->R Functions

double scalarDot(const Vector3 &a, const Vector3 &b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

#pragma mark - R3xR3->R3 Functions

Vector3 operator-(const Vector3 &a, const Vector3 &b) {
    return Vector3(a.x - b.x,
                   a.y - b.y,
                   a.z - b.z,
                   a.v - b.v);
}

Vector3 operator+(const Vector3 &a, const Vector3 &b) {
    return Vector3(a.x + b.x,
                   a.y + b.y,
                   a.z + b.z,
                   a.v + b.v);
}

void Vector3::operator-=(const Vector3 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    v -= other.v;
}

void Vector3::operator+=(const Vector3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    v += other.v;
}

Vector3 crossProduct(const Vector3 &a, const Vector3 &b) {
    return Vector3(a.y*b.z - a.z*b.y,
                   a.z*b.x - a.x*b.z,
                   a.x*b.y - a.y*b.x,
                   0.0); // CHECK?
}

