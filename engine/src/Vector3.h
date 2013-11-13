#ifndef __VECTOR3_H__
#define __VECTOR3_H__

class Vector3 {
public:
    union {
        struct {
            double x, y, z, v;
        };
        // allow array access too
        double coords[4];
    };
    /* int v; */

    Vector3(double x = 0, double y = 0, double z = 0, int v = 1);
    Vector3(const Vector3 &other);
    ~Vector3();

    // -> R3
    Vector3 operator-() const;
    // N -> R
    double &operator[](int i);
    const double &operator[](int i) const;
    // R3 -> R
    double module() const;
    // R3xR3 -> R3
    void operator-=(const Vector3 &other);
    void operator+=(const Vector3 &other);
    
    // R3 -> R3
    friend Vector3 normalizedVector(const Vector3 &v);
    // RxR3 -> R3
    friend Vector3 operator*(const float &a, const Vector3 &v);
    friend Vector3 operator*(const Vector3 &v, const float &a);
    // R3xR3 -> R
    friend double scalarDot(const Vector3 &a, const Vector3 &b);
    // R3xR3 -> R3
    friend Vector3 operator-(const Vector3 &a, const Vector3 &b);
    friend Vector3 operator+(const Vector3 &a, const Vector3 &b);
    friend Vector3 crossProduct(const Vector3 &a, const Vector3 &b);
};

#endif
