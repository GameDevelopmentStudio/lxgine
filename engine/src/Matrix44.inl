#include <math.h>
#include <string.h>

#include "Vector.h"

template <class T>
Matrix44<T>::Matrix44() {
}

template <class T>
Matrix44<T>::Matrix44(const Matrix44<T> &other) {
    load(other);
}

template <class T>
Matrix44<T>::~Matrix44() {
}

template <class T>
void Matrix44<T>::init(eInitializerIdentity) {
    matrix[0] = 1;    matrix[4] = 0;    matrix[8] = 0;    matrix[12] = 0;
    matrix[1] = 0;    matrix[5] = 1;    matrix[9] = 0;    matrix[13] = 0;
    matrix[2] = 0;    matrix[6] = 0;    matrix[10] = 1;   matrix[14] = 0;
    matrix[3] = 0;    matrix[7] = 0;   matrix[11] = 0;   matrix[15] = 1;
}

template <class T>
void Matrix44<T>::load(const Matrix44<T> &other) {
    memcpy(&matrix, other.getAsArray(), kNumElems * sizeof(T));
}

template <class T>
T* Matrix44<T>::getAsArray()
{
    return matrix;
}

template <class T>
const T* Matrix44<T>::getAsArray() const
{
    return matrix;
}

template <class T>
template <u8 col>
const Vector4<T>& Matrix44<T>::getCol() const {
    return (*reinterpret_cast<const Vector4<T>*>(&matrix[col * 4]));
}

template <class T>
template <u8 col>
Vector4<T>& Matrix44<T>::getCol() {
    return (*reinterpret_cast<Vector4<T>*>(&matrix[col * 4]));
}

template <class T>
T& Matrix44<T>::operator()(int i, int j) {
    return element(i, j);
}

template <class T>
const T& Matrix44<T>::operator()(int i, int j) const {
    return element(i, j);
}

template <class T>
T& Matrix44<T>::element(int i, int j) {
    return matrix[i << 2 | j];
}

template <class T>
const T& Matrix44<T>::element(int i, int j) const {
    return matrix[i << 2 | j];
}

template <class T>
void Matrix44<T>::setRow(int i, const Vector4<T> &p) {
    for (int j = 0; j < kNumRows; j++)
        element(i, j) = p[j];
}

template <class T>
void Matrix44<T>::setColumn(int j, const Vector4<T> &p) {
    for (int i = 0; i < kNumCols; i++)
        element(i, j) = p[i];
}

// Rotations
template <class T>
Matrix44<T> matrixWithXRotation(T alpha) {
    Matrix44<T> out;
    double sin_a = sin(alpha);
    double cos_a = cos(alpha);
    out.getAsArray()[0] = cos_a;    out.getAsArray()[1] = 0;    out.getAsArray()[2] = sin_a;    out.getAsArray()[3] = 0;
    out.getAsArray()[4] = 0;        out.getAsArray()[5] = 1;    out.getAsArray()[6] = 0;        out.getAsArray()[7] = 0;
    out.getAsArray()[8] = -sin_a;   out.getAsArray()[9] = 0;    out.getAsArray()[10] = cos_a;   out.getAsArray()[11] = 0;
    out.getAsArray()[12] = 0;       out.getAsArray()[13] = 0;   out.getAsArray()[14] = 0;       out.getAsArray()[15] = 1;
    return out;
}
template <class T>
Matrix44<T> matrixWithYRotation(T alpha) {
    Matrix44<T> out;
    double sin_a= sin(alpha);
    double cos_a= cos(alpha);
    out.getAsArray()[0] = 1;     out.getAsArray()[1] = 0;         out.getAsArray()[2] = 0;            out.getAsArray()[3] = 0;
    out.getAsArray()[4] = 0;     out.getAsArray()[5] = cos_a;     out.getAsArray()[6] = -sin_a;       out.getAsArray()[7] = 0;
    out.getAsArray()[8] = 0;     out.getAsArray()[9] = sin_a;     out.getAsArray()[10] = cos_a;       out.getAsArray()[11] = 0;
    out.getAsArray()[12] = 0;    out.getAsArray()[13] = 0;        out.getAsArray()[14] = 0;           out.getAsArray()[15] = 1;
    return out;
}

template <class T>
Matrix44<T> matrixWithZRotation(T alpha) {
    Matrix44<T> out;
    double sin_a = sin(alpha);
    double cos_a = cos(alpha);
    out.getAsArray()[0] = cos_a;    out.getAsArray()[1] = -sin_a;   out.getAsArray()[2] = 0;      out.getAsArray()[3] = 0;
    out.getAsArray()[4] = sin_a;    out.getAsArray()[5] = cos_a;    out.getAsArray()[6] = 0;      out.getAsArray()[7] = 0;
    out.getAsArray()[8] = 0;        out.getAsArray()[9] = 0;        out.getAsArray()[10] = 1;     out.getAsArray()[11] = 0;
    out.getAsArray()[12] = 0;       out.getAsArray()[13] = 0;       out.getAsArray()[14] = 0;     out.getAsArray()[15] = 1;
    return out;
}

template <class T>
Matrix44<T> matrixWithRotationOnAxis(T alpha, const Vector4<T> &a) {
    // center: rotation center
    // a: rotation axis
    //
    // By rotating over a default center, (0,0,0,1), we skip the last column of the matrix
    // (responsible for the traslation). This is useful when dealing with vector (in which
    // we don't care about their position)
    //
    // a vector is normalized, which means that operations like a.getX()^2 + a.getY()^2 
    // are equal to can be    to 1 - a.getZ()^2, which considerably simplifies the code

    double s = sin(alpha);
    double c = cos(alpha);
    double axx = a.getX()*a.getX();
    double ayy = a.getY()*a.getY();
    double azz = a.getZ()*a.getZ();

    Matrix44<T> out;
    out.getAsArray()[0] = axx + (1.f - axx) * c;
    out.getAsArray()[1] = a.getX() * a.getY() * (1.f - c) - a.getZ() * s;
    out.getAsArray()[2] = a.getX() * a.getZ() * (1.f - c) + a.getY() * s;
    out.getAsArray()[3] = 0;

    out.getAsArray()[4] = a.getX() * a.getY() * (1.f - c) + a.getZ() * s;
    out.getAsArray()[5] = ayy + (1.f - ayy) * c;
    out.getAsArray()[6] = a.getY() * a.getZ() * (1.f - c) - a.getX() * s;
    out.getAsArray()[7] = 0;

    out.getAsArray()[8] = a.getX() * a.getZ() * (1.f - c) - a.getY() * s;
    out.getAsArray()[9] = a.getY() * a.getZ() * (1.f - c) + a.getX() * s;
    out.getAsArray()[10] = azz + (1.f - azz) * c;
    out.getAsArray()[11] = 0;

    out.getAsArray()[12] = 0;
    out.getAsArray()[13] = 0;
    out.getAsArray()[14] = 0;
    out.getAsArray()[15] = 1;

    return out;
}

template <class T>
Matrix44<T> matrixWithRotationOnAxisWithCenter(T alpha, const Vector4<T> &a, const Vector4<T> &center) {
    // center: rotation center
    // a: rotation axis
    //
    // See Matrix44<T>::matrixWithRotationOnAxis for further explanation on the code
    double s = sin(alpha);
    double c = cos(alpha);
    double axx = a.getX()*a.getX();
    double ayy = a.getY()*a.getY();
    double azz = a.getZ()*a.getZ();

    Matrix44<T> out;
    out.getAsArray()[0] = axx + (1.f - axx) * c;
    out.getAsArray()[1] = a.getX() * a.getY() * (1.f - c) - a.getZ() * s;
    out.getAsArray()[2] = a.getX() * a.getZ() * (1.f - c) + a.getY() * s;
    out.getAsArray()[3] = (center.getX()*(1.f - axx) - a.getX()*(center.getY()*a.getY() + center.getZ()*a.getZ()))*(1.f - c) + (center.getY()*a.getZ() - center.getZ()*a.getY())*s;

    out.getAsArray()[4] = a.getX() * a.getY() * (1.f - c) + a.getZ() * s;
    out.getAsArray()[5] = ayy + (1.f - ayy) * c;
    out.getAsArray()[6] = a.getY() * a.getZ() * (1.f - c) - a.getX() * s;
    out.getAsArray()[7] = (center.getY()*(1.f - ayy) - a.getY()*(center.getX()*a.getX() + center.getZ()*a.getZ()))*(1.f - c) + (center.getZ()*a.getX() - center.getX()*a.getZ())*s;

    out.getAsArray()[8] = a.getX() * a.getZ() * (1.f - c) - a.getY() * s;
    out.getAsArray()[9] = a.getY() * a.getZ() * (1.f - c) + a.getX() * s;
    out.getAsArray()[10] = azz + (1.f - azz) * c;
    out.getAsArray()[11] = (center.getZ()*(1.f - azz) - a.getZ()*(center.getX()*a.getX() + center.getY()*a.getY()))*(1.f - c) + (center.getX()*a.getY() - center.getY()*a.getX())*s;

    out.getAsArray()[12] = 0;
    out.getAsArray()[13] = 0;
    out.getAsArray()[14] = 0;
    out.getAsArray()[15] = 1;

    return out;
}

// (R3->R3)x(R3->R3)->(R3->R3) Functions

template <class T>
Matrix44<T> operator *(const Matrix44<T> &A, const Matrix44<T> &B) {
    // Save result in tmp matrix to avoid conflicts between A, B and this
    Matrix44<T> out;

    for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                    out(i, j) = 0;
                    for (int k = 0; k < 4; k++) {
                        out(i,j) += A(i, k) * B(k, j);
                    }
            }
    }
    return out;
}

// (R3->R3)xR3->R3 Functions

template <class T>
Vector4<T> operator *(const Matrix44<T> &A, const Vector4<T> &p) {
    Vector4<T> out;
    for (int i = 0; i < 4; i++) {
        out[i] = 0;
        for (int j = 0; j < 4; j++) {
            out[i] += A(i,j) * p[j];
        }
    }
    return out;
}

// (R3->R3)->(R3->R3)

template <class T>
Matrix44<T> Matrix44<T>::inverse() const {
    // TODO: refactor to consider false cases
    Matrix44<T> out;

    out.getAsArray()[0] = matrix[5]    * matrix[10]   * matrix[15] -
                    matrix[5]    * matrix[11]   * matrix[14] -
                    matrix[9]    * matrix[6]    * matrix[15] +
                    matrix[9]    * matrix[7]    * matrix[14] +
                    matrix[13]   * matrix[6]    * matrix[11] -
                    matrix[13]   * matrix[7]    * matrix[10];

    out.getAsArray()[4] = -matrix[4]  * matrix[10]    * matrix[15] +
                    matrix[4]   * matrix[11]    * matrix[14] +
                    matrix[8]   * matrix[6]     * matrix[15] -
                    matrix[8]   * matrix[7]     * matrix[14] -
                    matrix[12]  * matrix[6]     * matrix[11] +
                    matrix[12]  * matrix[7]     * matrix[10];

    out.getAsArray()[8] = matrix[4]   * matrix[9]     * matrix[15] -
                    matrix[4]   * matrix[11]    * matrix[13] -
                    matrix[8]   * matrix[5]     * matrix[15] +
                    matrix[8]   * matrix[7]     * matrix[13] +
                    matrix[12]  * matrix[5]     * matrix[11] -
                    matrix[12]  * matrix[7]     * matrix[9];

    out.getAsArray()[12] = -matrix[4] * matrix[9]     * matrix[14] +
                     matrix[4]  * matrix[10]    * matrix[13] +
                     matrix[8]  * matrix[5]     * matrix[14] -
                     matrix[8]  * matrix[6]     * matrix[13] -
                     matrix[12] * matrix[5]     * matrix[10] +
                     matrix[12] * matrix[6]     * matrix[9];

    out.getAsArray()[1] = -matrix[1]  * matrix[10]    * matrix[15] +
                    matrix[1]   * matrix[11]    * matrix[14] +
                    matrix[9]   * matrix[2]     * matrix[15] -
                    matrix[9]   * matrix[3]     * matrix[14] -
                    matrix[13]  * matrix[2]     * matrix[11] +
                    matrix[13]  * matrix[3]     * matrix[10];

    out.getAsArray()[5] = matrix[0]   * matrix[10]    * matrix[15] -
                    matrix[0]   * matrix[11]    * matrix[14] -
                    matrix[8]   * matrix[2]     * matrix[15] +
                    matrix[8]   * matrix[3]     * matrix[14] +
                    matrix[12]  * matrix[2]     * matrix[11] -
                    matrix[12]  * matrix[3]     * matrix[10];

    out.getAsArray()[9] = -matrix[0]  * matrix[9]     * matrix[15] +
                    matrix[0]   * matrix[11]    * matrix[13] +
                    matrix[8]   * matrix[1]     * matrix[15] -
                    matrix[8]   * matrix[3]     * matrix[13] -
                    matrix[12]  * matrix[1]     * matrix[11] +
                    matrix[12]  * matrix[3]     * matrix[9];

    out.getAsArray()[13] = matrix[0]  * matrix[9]     * matrix[14] -
                     matrix[0]  * matrix[10]    * matrix[13] -
                     matrix[8]  * matrix[1]     * matrix[14] +
                     matrix[8]  * matrix[2]     * matrix[13] +
                     matrix[12] * matrix[1]     * matrix[10] -
                     matrix[12] * matrix[2]     * matrix[9];

    out.getAsArray()[2] = matrix[1]   * matrix[6]     * matrix[15] -
                    matrix[1]   * matrix[7]     * matrix[14] -
                    matrix[5]   * matrix[2]     * matrix[15] +
                    matrix[5]   * matrix[3]     * matrix[14] +
                    matrix[13]  * matrix[2]     * matrix[7] -
                    matrix[13]  * matrix[3]     * matrix[6];

    out.getAsArray()[6] = -matrix[0]  * matrix[6]     * matrix[15] +
                    matrix[0]   * matrix[7]     * matrix[14] +
                    matrix[4]   * matrix[2]     * matrix[15] -
                    matrix[4]   * matrix[3]     * matrix[14] -
                    matrix[12]  * matrix[2]     * matrix[7] +
                    matrix[12]  * matrix[3]     * matrix[6];

    out.getAsArray()[10] = matrix[0]  * matrix[5]     * matrix[15] -
                     matrix[0]  * matrix[7]     * matrix[13] -
                     matrix[4]  * matrix[1]     * matrix[15] +
                     matrix[4]  * matrix[3]     * matrix[13] +
                     matrix[12] * matrix[1]     * matrix[7] -
                     matrix[12] * matrix[3]     * matrix[5];

    out.getAsArray()[14] = -matrix[0] * matrix[5]     * matrix[14] +
                     matrix[0]  * matrix[6]     * matrix[13] +
                     matrix[4]  * matrix[1]     * matrix[14] -
                     matrix[4]  * matrix[2]     * matrix[13] -
                     matrix[12] * matrix[1]     * matrix[6] +
                     matrix[12] * matrix[2]     * matrix[5];

    out.getAsArray()[3] = -matrix[1]  * matrix[6]     * matrix[11] +
                    matrix[1]   * matrix[7]     * matrix[10] +
                    matrix[5]   * matrix[2]     * matrix[11] -
                    matrix[5]   * matrix[3]     * matrix[10] -
                    matrix[9]   * matrix[2]     * matrix[7] +
                    matrix[9]   * matrix[3]     * matrix[6];

    out.getAsArray()[7] = matrix[0]   * matrix[6]     * matrix[11] -
                    matrix[0]   * matrix[7]     * matrix[10] -
                    matrix[4]   * matrix[2]     * matrix[11] +
                    matrix[4]   * matrix[3]     * matrix[10] +
                    matrix[8]   * matrix[2]     * matrix[7] -
                    matrix[8]   * matrix[3]     * matrix[6];

    out.getAsArray()[11] = -matrix[0] * matrix[5]     * matrix[11] +
                     matrix[0]  * matrix[7]     * matrix[9] +
                     matrix[4]  * matrix[1]     * matrix[11] -
                     matrix[4]  * matrix[3]     * matrix[9] -
                     matrix[8]  * matrix[1]     * matrix[7] +
                     matrix[8]  * matrix[3]     * matrix[5];

    out.getAsArray()[15] = matrix[0]  * matrix[5]     * matrix[10] -
                     matrix[0]  * matrix[6]     * matrix[9] -
                     matrix[4]  * matrix[1]     * matrix[10] +
                     matrix[4]  * matrix[2]     * matrix[9] +
                     matrix[8]  * matrix[1]     * matrix[6] -
                     matrix[8]  * matrix[2]     * matrix[5];

    T det;
    det = matrix[0] * out.getAsArray()[0] + matrix[1] * out.getAsArray()[4] + matrix[2] * out.getAsArray()[8] + matrix[3] * out.getAsArray()[12];
    if (det == 0)
        out.init(kMatIdentity);
        return out;

    det = 1.0f / det;

    for (int i = 0; i < 16; i++)
        out.getAsArray()[i] = out.getAsArray()[i] * det;

    return out;
}