#ifndef __MATRIX3D_H__
#define __MATRIX3D_H__

class Point3D;

class Matrix3D {
public:
    double matrix[16];
    Matrix3D();
    Matrix3D(const Matrix3D &other);
    virtual ~Matrix3D();

    virtual void init();

    double &element(int i, int j);
    double &operator()(int i, int j);
    const double &element(int i, int j) const;
    const double &operator()(int i, int j) const;

    void setRow(int i, const Point3D &p);
    void setColumn(int j, const Point3D &p);

    // Transformations
    virtual void translate(double tx, double ty, double tz, bool premultiply=true);
    virtual void rotate(double rx, double ry, double rz, bool premultiply=true);
    void commit();

    // (R3->R3) -> (R3->R3)
    Matrix3D inverse() const;
};

// Rotations
// TODO: change this to use glRotate
Matrix3D matrixWithXRotation(double alpha);
Matrix3D matrixWithYRotation(double alpha);
Matrix3D matrixWithZRotation(double alpha);
Matrix3D matrixWithRotationOnAxis(double alpha, Point3D a);
Matrix3D matrixWithRotationOnAxisWithCenter(double alpha, Point3D a, Point3D center);
// (R3->R3)x(R3->R3) -> (R3->R3)
Matrix3D multiply(const Matrix3D &A, const Matrix3D &B);
// (R3->R3)xR3 -> R3
Point3D transformPoint(const Matrix3D &A, const Point3D &p);

#endif
