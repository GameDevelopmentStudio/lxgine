#include "Glut.h"
#include "Vector.h"

template<class T>
Transform3D<T>::Transform3D() {
}

template<class T>
Transform3D<T>::Transform3D(const Matrix44<T> &other) {
    matrix = other;
}

template<class T>
Transform3D<T>::~Transform3D() {
}

template<class T>
void Transform3D<T>::init() {
    matrix.init(Matrix44<T>::kMatIdentity);
}

template<class T>
const Matrix44<T>& Transform3D<T>::getAsArray() const {
    return matrix;
}

template<class T>
Matrix44<T>& Transform3D<T>::getAsArray() {
    return matrix;
}

template<class T>
const Vector3<T>& Transform3D<T>::getPosition() const {
    return matrix.template getCol<3>().getXYZ();
}

template<class T>
Vector3<T>& Transform3D<T>::getPosition() {
    return matrix.template getCol<3>().getXYZ();
}

template<class T>
const Vector3<T>& Transform3D<T>::getForward() const {
    return matrix.template getCol<0>().getXYZ();
}

template<class T>
Vector3<T>& Transform3D<T>::getForward() {
    return matrix.template getCol<0>().getXYZ();
}

template<class T>
const Vector3<T>& Transform3D<T>::getRight() const {
    return matrix.template getCol<1>().getXYZ();
}

template<class T>
Vector3<T>& Transform3D<T>::getRight() {
    return matrix.template getCol<1>().getXYZ();
}

template<class T>
const Vector3<T>& Transform3D<T>::getUp() const {
    return matrix.template getCol<2>().getXYZ();
}

template<class T>
Vector3<T>& Transform3D<T>::getUp() {
    return matrix.template getCol<2>().getXYZ();
}

template<class T>
void Transform3D<T>::setMatrix(const Matrix44<T>& v) {
    matrix = v;
}