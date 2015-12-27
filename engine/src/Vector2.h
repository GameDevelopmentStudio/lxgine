#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include "TypeDefinitions.h"

template <class T>
class Vector2 {
public:
    Vector2(T x = 0, T y = 0);
    Vector2(const Vector2<T> &other);
    ~Vector2();
    
    // Getters
    __inline const T& getX() const { return x; }
    __inline const T& getY() const { return y; }
    
    __inline T& getX() { return x; }
    __inline T& getY() { return y; }
    
    __inline void setX(const T& v) { x = v; }
    __inline void setY(const T& v) { y = v; }
    
    // -> R2
    Vector2<T> operator-() const;
    // N -> R
    T &operator[](int i);
    const T &operator[](int i) const;
    // R2 -> R
    T module() const;
    // R2xR2 -> R2
    void operator-=(const Vector2<T> &other);
    void operator+=(const Vector2<T> &other);
    
protected:
    union {
        struct {
            T x, y;
        };
        // allow array access too
        T coords[2];
    };
};

// R2 -> R2
template <class T> Vector2<T> normalizedVector(const Vector2<T> &v);
// RxR2 -> R2
template <class T> Vector2<T> operator*(const T &a, const Vector2<T> &v);
template <class T> Vector2<T> operator*(const Vector2<T> &v, const T &a);
// R2xR2 -> R
template <class T> T scalarDot(const Vector2<T> &a, const Vector2<T> &b);
// R2xR2 -> R2
template <class T> Vector2<T> operator-(const Vector2<T> &a, const Vector2<T> &b);
template <class T> Vector2<T> operator+(const Vector2<T> &a, const Vector2<T> &b);

typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;

typedef Vector2<real> Vec2;

/*******************
 * Implementation
 ******************/

#include "Vector2.inl"

#endif
