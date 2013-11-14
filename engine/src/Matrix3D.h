#ifndef __MATRIX3D_H__
#define __MATRIX3D_H__

#include <math.h>
#include "Vector4.h"
#include "Glut.h"

class Matrix3D {
public:
    float matrix[16];
    Matrix3D();
    Matrix3D(const Matrix3D &other);
    virtual ~Matrix3D();

    virtual void init();
    void load(const Matrix3D &other);

    float &element(int i, int j);
    float &operator()(int i, int j);
    const float &element(int i, int j) const;
    const float &operator()(int i, int j) const;

    void setRow(int i, const Vector4f &p);
    void setColumn(int j, const Vector4f &p);

    // floatransformations
    void translate(float tx, float ty, float tz, bool premultiply=true);
    void rotate(float rx, float ry, float rz, bool premultiply=true);
    void commit();

    // (R3->R3) -> (R3->R3)
    Matrix3D inverse() const;

    // (R3->R3)x(R3->R3) -> (R3->R3)
    friend Matrix3D operator *(const Matrix3D &A, const Matrix3D &B);
    // (R3->R3)xR3 -> R3
    friend Vector4<float> operator *(const Matrix3D &A, const Vector4<float> &p);
    
//    friend Matrix3D matrixWithXRotation(float alpha);
//    friend Matrix3D matrixWithYRotation(float alpha);
//    friend Matrix3D matrixWithZRotation(float alpha);
//    friend Matrix3D matrixWithRotationOnAxisWithCenter(float alpha, const Vector4<float> &a, const Vector4<float> &center);
//    friend Matrix3D matrixWithRotationOnAxis(float alpha, const Vector4<float> &a);
};

// TODO: change this to use glRotate
// Rotations
Matrix3D matrixWithXRotation(float alpha);
Matrix3D matrixWithYRotation(float alpha);
Matrix3D matrixWithZRotation(float alpha);
Matrix3D matrixWithRotationOnAxisWithCenter(float alpha, const Vector4f &a, const Vector4f &center);
Matrix3D matrixWithRotationOnAxis(float alpha, const Vector4<float> &a);

#endif