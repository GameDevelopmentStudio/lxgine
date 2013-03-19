#ifndef __LXPOINT3D_H__
#define __LXPOINT3D_H__

class LXMatrix3D;

class LXPoint3D
{
  public:
    double x, y, z;
    int v;

    LXPoint3D(double x = 0, double y = 0, double z = 0, int v = 1);
    ~LXPoint3D();

    // TODO: refactor
    // R -> R
    double getCoord(int index);
    void setCoord(int index, double value);
    // R3 -> R
    double module();
    // R3 -> R3
    void setValuesWithNormalizedVector(LXPoint3D *a);
    // R3xR3 -> R3
    void setValuesWithSubstraction(LXPoint3D *a, LXPoint3D *b);
    void setValuesWithAddition(LXPoint3D *a, LXPoint3D *b);
    void setValuesWithCrossProduct(LXPoint3D *a, LXPoint3D *b);
    // (R3->R3)xR3 -> R3
    void setValuesWithTransformation(LXMatrix3D *matrix, LXPoint3D *point);
};

// R3xR3 -> R
double scalarDot(LXPoint3D *a, LXPoint3D *b);

#endif
