#ifndef __Matrix44f_H__
#define __Matrix44f_H__

#include "TypeDefinitions.h"

template <class T> class Vector4;

template <class T>
class Matrix44 {
public:
    enum eInitializerIdentity { kMatIdentity };
    
    Matrix44();
    Matrix44(const Matrix44<T> &other);
    ~Matrix44();

    void init(eInitializerIdentity);
    void load(const Matrix44<T> &other);

    T* getAsArray();
    const T* getAsArray() const;
    
    template <u8 col> const Vector4<T>& getCol() const;
    template <u8 col> Vector4<T>& getCol();
    
    T& element(int i, int j);
    T& operator()(int i, int j);
    const T& element(int i, int j) const;
    const T& operator()(int i, int j) const;

    void setRow(int i, const Vector4<T> &p);
    void setColumn(int j, const Vector4<T> &p);

    // (R3->R3) -> (R3->R3)
    Matrix44 inverse() const;
    
protected:
    
    enum { kNumRows = 4, kNumCols = 4, kNumElems = kNumRows * kNumCols };
    T matrix[kNumElems];
};

// (R3->R3)x(R3->R3) -> (R3->R3)
template <class T> Matrix44<T> operator *(const Matrix44<T> &A, const Matrix44<T> &B);
// (R3->R3)xR3 -> R3
template <class T> Vector4<T> operator *(const Matrix44<T> &A, const Vector4<T> &p);

// Rotations
template <class T> Matrix44<T> matrixWithXRotation(T alpha);
template <class T> Matrix44<T> matrixWithYRotation(T alpha);
template <class T> Matrix44<T> matrixWithZRotation(T alpha);
template <class T> Matrix44<T> matrixWithRotationOnAxisWithCenter(T alpha, const Vector4<T> &a, const Vector4<T> &center);
template <class T> Matrix44<T> matrixWithRotationOnAxis(T alpha, const Vector4<T> &a);

typedef Matrix44<float> Matrix44f;
typedef Matrix44<double> Matrix44d;

typedef Matrix44<real> Mat44;

/*******************
 * Implementation
 ******************/

#include "Matrix44.inl"

#endif