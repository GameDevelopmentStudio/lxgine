#include "MathPrimitives.h"

template <class T>
Vector3<T>::Vector3(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template <class T>
Vector3<T>::Vector3(const Vector3<T> &other) {
    x = other.getX();
    y = other.getY();
    z = other.getZ();
}

template <class T>
Vector3<T>::Vector3(const Vector2<T> &other, const T v2) {
    this->x = other.getX();
    this->y = other.getY();
    this->z = v2;
}

template <class T>
Vector3<T>::~Vector3() {
}

// N->R Functions

template <class T>
T &Vector3<T>::operator[](int i) {
    return coords[i];
}

template <class T>
const T &Vector3<T>::operator[](int i) const {
    return coords[i];
}

// R3->R Functions

template <class T>
T Vector3<T>::module() const {
    return sqrt(scalarDot(*this, *this));
}

// R3->R3 Functions

template <class T>
Vector3<T> Vector3<T>::operator-() const {
    return Vector3<T>(-x, -y, -z);
}

template <class T>
Vector3<T> normalizedVector(const Vector3<T> &v) {
    T mod = v.module();
    return Vector3<T>(v.getX() / mod,
                      v.getY() / mod,
                      v.getZ() / mod);
}

// RxR3->R3 Functions

template <class T>
Vector3<T> operator*(const T &a, const Vector3<T> &v) {
    return Vector3<T>(a * v.getX(),
                      a * v.getY(),
                      a * v.getZ());
}

template <class T>
Vector3<T> operator*(const Vector3<T> &v, const T &a) {
    return Vector3<T>(v.getX() * a,
                      v.getY() * a,
                      v.getZ() * a);
}

template <class T>
Vector3<T> operator/(const Vector3<T> &v, const T &a) {
    return Vector3<T>(v.getX() / a,
                      v.getY() / a,
                      v.getZ() / a);
}

// R3xR3->R Functions

template <class T>
T scalarDot(const Vector3<T> &a, const Vector3<T> &b) {
    return a.getX()*b.getX() + a.getY()*b.getY() + a.getZ()*b.getZ();
}

// R3xR3->R3 Functions

template <class T>
Vector3<T> operator-(const Vector3<T> &a, const Vector3<T> &b) {
    return Vector3<T>(a.getX() - b.getX(),
                      a.getY() - b.getY(),
                      a.getZ() - b.getZ());
}

template <class T>
Vector3<T> operator+(const Vector3<T> &a, const Vector3<T> &b) {
    return Vector3<T>(a.getX() + b.getX(),
                      a.getY() + b.getY(),
                      a.getZ() + b.getZ());
}

template <class T>
void Vector3<T>::operator-=(const Vector3<T> &other) {
    x -= other.getX();
    y -= other.getY();
    z -= other.getZ();
}

template <class T>
void Vector3<T>::operator+=(const Vector3<T> &other) {
    x += other.getX();
    y += other.getY();
    z += other.getZ();
}

template <class T>
bool Vector3<T>::operator==(const Vector3<T> &other) const {
    return (abs(x - other.x) < kVectorEqualityDelta)
        && (abs(y - other.y) < kVectorEqualityDelta)
        && (abs(z - other.z) < kVectorEqualityDelta);
}

template <class T>
Vector3<T> crossProduct(const Vector3<T> &a, const Vector3<T> &b) {
    return Vector3<T>(a.getY()*b.getZ() - a.getZ()*b.getY(),
                      a.getZ()*b.getX() - a.getX()*b.getZ(),
                      a.getX()*b.getY() - a.getY()*b.getX());
}