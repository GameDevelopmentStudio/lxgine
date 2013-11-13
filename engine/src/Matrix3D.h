#ifndef __MATRIX3D_H__
#define __MATRIX3D_H__

#include "Vector3.h"

class Matrix3D {
public:
    double matrix[16];
    Matrix3D();
    Matrix3D(const Matrix3D &other);
    virtual ~Matrix3D();

    virtual void init();
    void load(const Matrix3D &other);

    double &element(int i, int j);
    double &operator()(int i, int j);
    const double &element(int i, int j) const;
    const double &operator()(int i, int j) const;

    void setRow(int i, const Vector3 &p);
    void setColumn(int j, const Vector3 &p);

    // Transformations
    void translate(double tx, double ty, double tz, bool premultiply=true);
    void rotate(double rx, double ry, double rz, bool premultiply=true);
    void commit();

    // (R3->R3) -> (R3->R3)
    Matrix3D inverse() const;

    // (R3->R3)x(R3->R3) -> (R3->R3)
    friend Matrix3D operator *(const Matrix3D &A, const Matrix3D &B);
    // (R3->R3)xR3 -> R3
    friend Vector3 operator *(const Matrix3D &A, const Vector3 &p);
};

// TODO: change this to use glRotate
// Rotations
Matrix3D matrixWithXRotation(double alpha);
Matrix3D matrixWithYRotation(double alpha);
Matrix3D matrixWithZRotation(double alpha);
Matrix3D matrixWithRotationOnAxisWithCenter(double alpha, const Vector3 &a, const Vector3 &center);
Matrix3D matrixWithRotationOnAxis(double alpha, const Vector3 &a);

#endif
