#ifndef __LXPOINT3D_H__
#define __LXPOINT3D_H__

class LXMatrix3D;

class LXPoint3D {
  public:
    union {
      struct {
        double x, y, z, v;
      };
      // allow array access too
      double coords[4];
    };
    /* int v; */

    LXPoint3D(double x = 0, double y = 0, double z = 0, int v = 1);
    LXPoint3D(const LXPoint3D &other);
    ~LXPoint3D();

    // -> R3
    LXPoint3D operator-() const;
    // N -> R
    double &operator[](int i);
    const double &operator[](int i) const;
    // R3 -> R
    double module() const;
};

// R3 -> R3
LXPoint3D normalizedVector(const LXPoint3D &v);
// RxR3 -> R3
LXPoint3D operator*(const float &a, const LXPoint3D &v);
LXPoint3D operator*(const LXPoint3D &v, const float &a);
// R3xR3 -> R
double scalarDot(const LXPoint3D &a, const LXPoint3D &b);
// R3xR3 -> R3
LXPoint3D operator-(const LXPoint3D &a, const LXPoint3D &b);
LXPoint3D operator+(const LXPoint3D &a, const LXPoint3D &b);
LXPoint3D crossProduct(const LXPoint3D &a, const LXPoint3D &b);

#endif
