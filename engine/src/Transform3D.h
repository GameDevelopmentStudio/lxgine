#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "TypeDefinitions.h"
#include "Matrix44.h"

template <class T> class Matrix44;

template <class T>
class Transform3D {
public:
    Transform3D();
    Transform3D(const Matrix44<T> &other);
    ~Transform3D();
    
    void init();
    
    const Matrix44<T>& getAsArray() const;
    Matrix44<T>& getAsArray();
    
    const Vector3<T>& getPosition() const;
    Vector3<T>& getPosition();
    const Vector3<T>& getForward() const;
    Vector3<T>& getForward();
    const Vector3<T>& getRight() const;
    Vector3<T>& getRight();
    const Vector3<T>& getUp() const;
    Vector3<T>& getUp();
    
    void setMatrix(const Matrix44<T>& v);

    // float transformations
    void translate(T tx, T ty, T tz, bool premultiply=true);
    void rotate(T rx, T ry, T rz, bool premultiply=true);
    void commit();
    
protected:
    Matrix44<T> matrix;
};

typedef Transform3D<float> Transformf;
typedef Transform3D<double> Transformd;

typedef Transform3D<real> Transform;

/*******************
 * Implementation
 ******************/

#include "Transform3D.inl"

#endif
