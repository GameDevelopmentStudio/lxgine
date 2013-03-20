#ifndef __LXMATRIX3D_H__
#define __LXMATRIX3D_H__

class LXPoint3D;

class LXMatrix3D {
  public:
    double matrix[16];
    
    LXMatrix3D();
    LXMatrix3D(const LXMatrix3D &other);
    ~LXMatrix3D();

    void init();

    double &element(int i, int j);
    double &operator()(int i, int j);
    const double &element(int i, int j) const;
    const double &operator()(int i, int j) const;

    void setRow(int i, const LXPoint3D &p);
    void setColumn(int j, const LXPoint3D &p);

    // Transformations
    void translate(double tx, double ty, double tz);
    void rotate(double rx, double ry, double rz);
    void commit();
};

// Rotations
// TODO: change this to use glRotate
LXMatrix3D matrixWithXRotation(double alpha);
LXMatrix3D matrixWithYRotation(double alpha);
LXMatrix3D matrixWithZRotation(double alpha);
// (R3->R3)x(R3->R3) -> (R3->R3)
LXMatrix3D multiply(const LXMatrix3D &A, const LXMatrix3D &B);
// (R3->R3)xR3 -> R3
LXPoint3D transformPoint(const LXMatrix3D &A, const LXPoint3D &p);

#endif
