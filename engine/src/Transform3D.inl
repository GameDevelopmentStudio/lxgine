#include "Glut.h"

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
const Matrix44<T>& Transform3D<T>::getMatrix() const {
    return matrix;
}

template<class T>
Matrix44<T>& Transform3D<T>::getMatrix() {
    return matrix;
}

template<class T>
void Transform3D<T>::setMatrix(const Matrix44<T>& v) {
    matrix = v;
}