#ifndef __LXMATRIX3D_H__
#define __LXMATRIX3D_H__

#include "LXPoint3D.h"

class LXMatrix3D
{
  public:

    double matrix[16];
    
    LXMatrix3D();
    ~LXMatrix3D();

    void init();

    void setRow(int i, LXPoint3D *p);
    void setColumn(int j, LXPoint3D *p);
    double get(int i, int j);
    double set(int i, int j, double value);
    
    void setValuesWithMultiplication(LXMatrix3D* A, LXMatrix3D* B);
    void setValuesWithXRotation(double alpha);
    void setValuesWithYRotation(double alpha);
    void setValuesWithZRotation(double alpha);

    // Transformations
    void translate(double tx, double ty, double tz);
    void rotate(double rx, double ry, double rz);
    void commit();
};

#endif
