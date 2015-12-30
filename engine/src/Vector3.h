#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include "TypeDefinitions.h"

template <class T> class Vector2;

template <class T>
class Vector3 {
public:
    Vector3<T>(T x = 0, T y = 0, T z = 0);
    Vector3<T>(const Vector3<T> &other);
    explicit Vector3<T>(const Vector2<T> &other, T z);
    explicit Vector3<T>(T x, const Vector2<T> &other);
    ~Vector3<T>();

    // Getters
    __inline const T& getX() const { return x; }
    __inline const T& getY() const { return y; }
    __inline const T& getZ() const { return z; }
    
    __inline T& getX() { return x; }
    __inline T& getY() { return y; }
    __inline T& getZ() { return z; }
    
    __inline void setX(const T& v) { x = v; }
    __inline void setY(const T& v) { y = v; }
    __inline void setZ(const T& v) { z = v; }
    
    // -> R3
    Vector3<T> operator-() const;
    // N -> R
    T &operator[](int i);
    const T &operator[](int i) const;
    // R3 -> R
    T module() const;
    // R3xR3 -> R3
    void operator-=(const Vector3<T> &other);
    void operator+=(const Vector3<T> &other);
protected:
    union {
        struct {
            T x, y, z;
        };
        // allow array access too
        T coords[3];
    };
};

// R3 -> R3
template <class T> Vector3<T> normalizedVector(const Vector3<T> &v);
// RxR3 -> R3
template <class T> Vector3<T> operator*(const T &a, const Vector3<T> &v);
template <class T> Vector3<T> operator*(const Vector3<T> &v, const T &a);
template <class T> Vector3<T> operator/(const Vector3<T> &v, const T &a);
// R3xR3 -> R
template <class T> T scalarDot(const Vector3<T> &a, const Vector3<T> &b);
// R3xR3 -> R3
template <class T> Vector3<T> operator-(const Vector3<T> &a, const Vector3<T> &b);
template <class T> Vector3<T> operator+(const Vector3<T> &a, const Vector3<T> &b);
template <class T> Vector3<T> crossProduct(const Vector3<T> &a, const Vector3<T> &b);

typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;

typedef Vector3<real> Vec3;

/*******************
 * Implementation
 ******************/

#include "Vector3.inl"

#endif
