#include "Vector2.h"
#include "Matrix3D.h"
#include <math.h>

#include <iostream>

Vector2::Vector2(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector2::Vector2(const Vector2 &other) {
    x = other.x;
    y = other.y;
}

Vector2::~Vector2() {
}

#pragma mark - N->R Functions

double &Vector2::operator[](int i) {
    return coords[i];
}

const double &Vector2::operator[](int i) const {
    return coords[i];
}

#pragma mark - R2->R Functions

double Vector2::module() const {
    return sqrt(scalarDot(*this, *this));
}

#pragma mark - R2->R2 Functions

Vector2 Vector2::operator-() const {
    return Vector2(-x, -y);
}

Vector2 normalizedVector(const Vector2 &v) {
    double mod = v.module();
    return Vector2(v.x / mod,
                   v.y / mod);
}

#pragma mark - RxR2->R2 Functions

Vector2 operator*(const float &a, const Vector2 &v) {
    return Vector2(a * v.x,
                   a * v.y);
}

Vector2 operator*(const Vector2 &v, const float &a) {
    return Vector2(v.x * a,
                   v.y * a);
}

#pragma mark - R2xR2->R Functions

double scalarDot(const Vector2 &a, const Vector2 &b) {
    return a.x*b.x + a.y*b.y;
}

#pragma mark - R2xR2->R2 Functions

Vector2 operator-(const Vector2 &a, const Vector2 &b) {
    return Vector2(a.x - b.x,
                   a.y - b.y);
}

Vector2 operator+(const Vector2 &a, const Vector2 &b) {
    return Vector2(a.x + b.x,
                   a.y + b.y);
}

void Vector2::operator-=(const Vector2 &other) {
    x -= other.x;
    y -= other.y;
}

void Vector2::operator+=(const Vector2 &other) {
    x += other.x;
    y += other.y;
}