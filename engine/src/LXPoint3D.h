#ifndef __LXPOINT3D_H__
#define __LXPOINT3D_H__

class LXMatrix3D;

class LXPoint3D {
  public:
    double x, y, z;
    int v;

    LXPoint3D(double x = 0, double y = 0, double z = 0, int v = 1);
    LXPoint3D(const LXPoint3D &other);
    ~LXPoint3D();

    // R -> R
    double getCoord(int index) const;
    void setCoord(int index, double value);
    // R3 -> R
    double module() const;
};

// R3 -> R3
LXPoint3D normalizedVector(const LXPoint3D &v);
// R3xR3 -> R
double scalarDot(const LXPoint3D &a, const LXPoint3D &b);
// R3xR3 -> R3
LXPoint3D operator-(const LXPoint3D &a, const LXPoint3D &b);
LXPoint3D operator+(const LXPoint3D &a, const LXPoint3D &b);
LXPoint3D crossProduct(const LXPoint3D &a, const LXPoint3D &b);

#endif
