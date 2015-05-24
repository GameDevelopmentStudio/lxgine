#ifndef __VECTOR4_H__
#define __VECTOR4_H__

#include "TypeDefinitions.h"

template <class T> class Vector2;
template <class T> class Vector3;

template <class T>
class Vector4 {
public:
    Vector4(T x = 0, T y = 0, T z = 0, T w = 1);
    Vector4(const Vector4 &other);
    explicit Vector4(const Vector3<T> &other, const T v3);
    explicit Vector4(const Vector2<T> &other, const T v2, const T v3);
    ~Vector4();

    // Getters
    __inline const T& getX() const { return x; }
    __inline const T& getY() const { return y; }
    __inline const T& getZ() const { return z; }
    __inline const T& getW() const { return w; }
    
    __inline T& getX() { return x; }
    __inline T& getY() { return y; }
    __inline T& getZ() { return z; }
    __inline T& getW() { return w; }
    
    __inline void setX(const T& v) { x = v; }
    __inline void setY(const T& v) { y = v; }
    __inline void setZ(const T& v) { z = v; }
    __inline void setW(const T& v) { w = v; }
    
    // -> R3
    Vector4<T> operator-() const;
    // N -> R
    T &operator[](int i);
    const T &operator[](int i) const;
    // R3 -> R
    T module() const;
    // R3xR3 -> R3
    void operator-=(const Vector4<T> &other);
    void operator+=(const Vector4<T> &other);
    
protected:
    union {
        struct {
            T x, y, z, w;
        };
        // allow array access too
        T coords[4];
    };
};

// R3 -> R3
template <class T> Vector4<T> normalizedVector(const Vector4<T> &v);
// RxR3 -> R3
template <class T> Vector4<T> operator*(const float &a, const Vector4<T> &v);
template <class T> Vector4<T> operator*(const Vector4<T> &v, const T &a);
// R3xR3 -> R
template <class T> T scalarDot(const Vector4<T> &a, const Vector4<T> &b);
// R3xR3 -> R3
template <class T> Vector4<T> operator-(const Vector4<T> &a, const Vector4<T> &b);
template <class T> Vector4<T> operator+(const Vector4<T> &a, const Vector4<T> &b);
template <class T> Vector4<T> crossProduct(const Vector4<T> &a, const Vector4<T> &b);

typedef Vector4<float> Vector4f;
typedef Vector4<double> Vector4d;

typedef Vector4<real> Vec4;

/*******************
 * Implementation
 ******************/

#include "Vector4.inl"

#endif