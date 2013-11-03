#ifndef __POINT3D_H__
#define __POINT3D_H__

class Matrix3D;

class Point3D {
public:
    union {
        struct {
            double x, y, z, v;
        };
        // allow array access too
        double coords[4];
    };
    /* int v; */

    Point3D(double x = 0, double y = 0, double z = 0, int v = 1);
    Point3D(const Point3D &other);
    ~Point3D();

    // -> R3
    Point3D operator-() const;
    // N -> R
    double &operator[](int i);
    const double &operator[](int i) const;
    // R3 -> R
    double module() const;
    // R3xR3 -> R3
    void operator-=(const Point3D &other);
    void operator+=(const Point3D &other);
};

// R3 -> R3
Point3D normalizedVector(const Point3D &v);
// RxR3 -> R3
Point3D operator*(const float &a, const Point3D &v);
Point3D operator*(const Point3D &v, const float &a);
// R3xR3 -> R
double scalarDot(const Point3D &a, const Point3D &b);
// R3xR3 -> R3
Point3D operator-(const Point3D &a, const Point3D &b);
Point3D operator+(const Point3D &a, const Point3D &b);
Point3D crossProduct(const Point3D &a, const Point3D &b);

#endif
