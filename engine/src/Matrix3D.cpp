#include "Matrix3D.h"
#include <math.h>

#include "Glut.h"
#include "Vector4.h"

Matrix3D::Matrix3D() {
}

Matrix3D::Matrix3D(const Matrix3D &other) {
    load(other);
}

Matrix3D::~Matrix3D() {
}

void Matrix3D::init() {
    matrix[0] = 1;    matrix[1] = 0;    matrix[2] = 0;    matrix[3] = 0;
    matrix[4] = 0;    matrix[5] = 1;    matrix[6] = 0;    matrix[7] = 0;
    matrix[8] = 0;    matrix[9] = 0;    matrix[10] = 1;   matrix[11] = 0;
    matrix[12] = 0;   matrix[13] = 0;   matrix[14] = 0;   matrix[15] = 1;
}

void Matrix3D::load(const Matrix3D &other) {
    for (int n = 0; n < 16; n++) {
        matrix[n] = other.matrix[n];
    }
}

float &Matrix3D::operator()(int i, int j) {
    return element(i, j);
}

const float &Matrix3D::operator()(int i, int j) const {
    return element(i, j);
}

float &Matrix3D::element(int i, int j) {
    return matrix[i << 2 | j];
}

const float &Matrix3D::element(int i, int j) const {
    return matrix[i << 2 | j];
}

void Matrix3D::setRow(int i, const Vector4f &p) {
    for (int j = 0; j < 4; j++)
        element(i, j) = p[j];
}

void Matrix3D::setColumn(int j, const Vector4f &p) {
    for (int i = 0; i < 4; i++)
        element(i, j) = p[i];
}

// Transformations

// Transformations
void Matrix3D::translate(float tx, float ty, float tz, bool premultiply) {

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        glTranslated(tx, ty, tz);
        Matrix3D transform;
        glGetFloatv(GL_MODELVIEW_MATRIX, transform.matrix);
    glPopMatrix();

    // Apply transform to one's matrix
    Matrix3D self = *this;
    if (premultiply)
        load(transform * self);
    else
        load(self * transform);
}

void Matrix3D::rotate(float rx, float ry, float rz, bool premultiply) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        if (rx != 0)
            glRotated(rx, 1, 0, 0);
        if (ry != 0)
            glRotated(ry, 0, 0, 1);
        if (rz != 0)
            glRotated(rz, 0, 1, 0);
        Matrix3D transform;
        glGetFloatv(GL_MODELVIEW_MATRIX, transform.matrix);
    glPopMatrix();

    // Apply transform to one's matrix
    Matrix3D self = *this;
    if (premultiply)
        load(transform * self);
    else
        load(self * transform);
}

// Rotations

Matrix3D matrixWithXRotation(float alpha) {
    Matrix3D out;
    double sin_a = sin(alpha);
    double cos_a = cos(alpha);
    out.matrix[0] = cos_a;    out.matrix[1] = 0;    out.matrix[2] = sin_a;    out.matrix[3] = 0;
    out.matrix[4] = 0;        out.matrix[5] = 1;    out.matrix[6] = 0;        out.matrix[7] = 0;
    out.matrix[8] = -sin_a;   out.matrix[9] = 0;    out.matrix[10] = cos_a;   out.matrix[11] = 0;
    out.matrix[12] = 0;       out.matrix[13] = 0;   out.matrix[14] = 0;       out.matrix[15] = 1;
    return out;
}

Matrix3D matrixWithYRotation(float alpha) {
    Matrix3D out;
    double sin_a= sin(alpha);
    double cos_a= cos(alpha);
    out.matrix[0] = 1;     out.matrix[1] = 0;         out.matrix[2] = 0;            out.matrix[3] = 0;
    out.matrix[4] = 0;     out.matrix[5] = cos_a;     out.matrix[6] = -sin_a;       out.matrix[7] = 0;
    out.matrix[8] = 0;     out.matrix[9] = sin_a;     out.matrix[10] = cos_a;       out.matrix[11] = 0;
    out.matrix[12] = 0;    out.matrix[13] = 0;        out.matrix[14] = 0;           out.matrix[15] = 1;
    return out;
}

Matrix3D matrixWithZRotation(float alpha) {
    Matrix3D out;
    double sin_a= sin(alpha);
    double cos_a= cos(alpha);
    out.matrix[0] = cos_a;    out.matrix[1] = -sin_a;   out.matrix[2] = 0;      out.matrix[3] = 0;
    out.matrix[4] = sin_a;    out.matrix[5] = cos_a;    out.matrix[6] = 0;      out.matrix[7] = 0;
    out.matrix[8] = 0;        out.matrix[9] = 0;        out.matrix[10] = 1;     out.matrix[11] = 0;
    out.matrix[12] = 0;       out.matrix[13] = 0;       out.matrix[14] = 0;     out.matrix[15] = 1;
    return out;
}

Matrix3D matrixWithRotationOnAxis(float alpha, const Vector4f &a) {
    // center: rotation center
    // a: rotation axis
    //
    // By rotating over a default center, (0,0,0,1), we skip the last column of the matrix
    // (responsible for the traslation). This is useful when dealing with vector (in which
    // we don't care about their position)
    //
    // a vector is normalized, which means that operations like a.x^2 + a.y^2 
    // are equal to can be    to 1 - a.z^2, which considerably simplifies the code

    double s = sin(alpha);
    double c = cos(alpha);
    double axx = a.x*a.x;
    double ayy = a.y*a.y;
    double azz = a.z*a.z;

    Matrix3D out;
    out.matrix[0] = axx + (1.f - axx) * c;
    out.matrix[1] = a.x * a.y * (1.f - c) - a.z * s;
    out.matrix[2] = a.x * a.z * (1.f - c) + a.y * s;
    out.matrix[3] = 0;

    out.matrix[4] = a.x * a.y * (1.f - c) + a.z * s;
    out.matrix[5] = ayy + (1.f - ayy) * c;
    out.matrix[6] = a.y * a.z * (1.f - c) - a.x * s;
    out.matrix[7] = 0;

    out.matrix[8] = a.x * a.z * (1.f - c) - a.y * s;
    out.matrix[9] = a.y * a.z * (1.f - c) + a.x * s;
    out.matrix[10] = azz + (1.f - azz) * c;
    out.matrix[11] = 0;

    out.matrix[12] = 0;
    out.matrix[13] = 0;
    out.matrix[14] = 0;
    out.matrix[15] = 1;

    return out;
}

Matrix3D matrixWithRotationOnAxisWithCenter(float alpha, const Vector4f &a, const Vector4f &center) {
    // center: rotation center
    // a: rotation axis
    //
    // See Matrix3D::matrixWithRotationOnAxis for further explanation on the code
    double s = sin(alpha);
    double c = cos(alpha);
    double axx = a.x*a.x;
    double ayy = a.y*a.y;
    double azz = a.z*a.z;

    Matrix3D out;
    out.matrix[0] = axx + (1.f - axx) * c;
    out.matrix[1] = a.x * a.y * (1.f - c) - a.z * s;
    out.matrix[2] = a.x * a.z * (1.f - c) + a.y * s;
    out.matrix[3] = (center.x*(1.f - axx) - a.x*(center.y*a.y + center.z*a.z))*(1.f - c) + (center.y*a.z - center.z*a.y)*s;

    out.matrix[4] = a.x * a.y * (1.f - c) + a.z * s;
    out.matrix[5] = ayy + (1.f - ayy) * c;
    out.matrix[6] = a.y * a.z * (1.f - c) - a.x * s;
    out.matrix[7] = (center.y*(1.f - ayy) - a.y*(center.x*a.x + center.z*a.z))*(1.f - c) + (center.z*a.x - center.x*a.z)*s;

    out.matrix[8] = a.x * a.z * (1.f - c) - a.y * s;
    out.matrix[9] = a.y * a.z * (1.f - c) + a.x * s;
    out.matrix[10] = azz + (1.f - azz) * c;
    out.matrix[11] = (center.z*(1.f - azz) - a.z*(center.x*a.x + center.y*a.y))*(1.f - c) + (center.x*a.y - center.y*a.x)*s;

    out.matrix[12] = 0;
    out.matrix[13] = 0;
    out.matrix[14] = 0;
    out.matrix[15] = 1;

    return out;
}

// (R3->R3)x(R3->R3)->(R3->R3) Functions

Matrix3D operator *(const Matrix3D &A, const Matrix3D &B) {
    // Save result in tmp matrix to avoid conflicts between A, B and this
    Matrix3D out;

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

Vector4f operator *(const Matrix3D &A, const Vector4f &p) {
    Vector4f out;
    for (int i = 0; i < 4; i++) {
        out[i] = 0;
        for (int j = 0; j < 4; j++) {
            out[i] += A(i,j) * p[j];
        }
    }
    return out;
}

// (R3->R3)->(R3->R3)

Matrix3D Matrix3D::inverse() const {
    // TODO: refactor to consider false cases
    Matrix3D out;

    out.matrix[0] = matrix[5]    * matrix[10]   * matrix[15] -
                    matrix[5]    * matrix[11]   * matrix[14] -
                    matrix[9]    * matrix[6]    * matrix[15] +
                    matrix[9]    * matrix[7]    * matrix[14] +
                    matrix[13]   * matrix[6]    * matrix[11] -
                    matrix[13]   * matrix[7]    * matrix[10];

    out.matrix[4] = -matrix[4]  * matrix[10]    * matrix[15] +
                    matrix[4]   * matrix[11]    * matrix[14] +
                    matrix[8]   * matrix[6]     * matrix[15] -
                    matrix[8]   * matrix[7]     * matrix[14] -
                    matrix[12]  * matrix[6]     * matrix[11] +
                    matrix[12]  * matrix[7]     * matrix[10];

    out.matrix[8] = matrix[4]   * matrix[9]     * matrix[15] -
                    matrix[4]   * matrix[11]    * matrix[13] -
                    matrix[8]   * matrix[5]     * matrix[15] +
                    matrix[8]   * matrix[7]     * matrix[13] +
                    matrix[12]  * matrix[5]     * matrix[11] -
                    matrix[12]  * matrix[7]     * matrix[9];

    out.matrix[12] = -matrix[4] * matrix[9]     * matrix[14] +
                     matrix[4]  * matrix[10]    * matrix[13] +
                     matrix[8]  * matrix[5]     * matrix[14] -
                     matrix[8]  * matrix[6]     * matrix[13] -
                     matrix[12] * matrix[5]     * matrix[10] +
                     matrix[12] * matrix[6]     * matrix[9];

    out.matrix[1] = -matrix[1]  * matrix[10]    * matrix[15] +
                    matrix[1]   * matrix[11]    * matrix[14] +
                    matrix[9]   * matrix[2]     * matrix[15] -
                    matrix[9]   * matrix[3]     * matrix[14] -
                    matrix[13]  * matrix[2]     * matrix[11] +
                    matrix[13]  * matrix[3]     * matrix[10];

    out.matrix[5] = matrix[0]   * matrix[10]    * matrix[15] -
                    matrix[0]   * matrix[11]    * matrix[14] -
                    matrix[8]   * matrix[2]     * matrix[15] +
                    matrix[8]   * matrix[3]     * matrix[14] +
                    matrix[12]  * matrix[2]     * matrix[11] -
                    matrix[12]  * matrix[3]     * matrix[10];

    out.matrix[9] = -matrix[0]  * matrix[9]     * matrix[15] +
                    matrix[0]   * matrix[11]    * matrix[13] +
                    matrix[8]   * matrix[1]     * matrix[15] -
                    matrix[8]   * matrix[3]     * matrix[13] -
                    matrix[12]  * matrix[1]     * matrix[11] +
                    matrix[12]  * matrix[3]     * matrix[9];

    out.matrix[13] = matrix[0]  * matrix[9]     * matrix[14] -
                     matrix[0]  * matrix[10]    * matrix[13] -
                     matrix[8]  * matrix[1]     * matrix[14] +
                     matrix[8]  * matrix[2]     * matrix[13] +
                     matrix[12] * matrix[1]     * matrix[10] -
                     matrix[12] * matrix[2]     * matrix[9];

    out.matrix[2] = matrix[1]   * matrix[6]     * matrix[15] -
                    matrix[1]   * matrix[7]     * matrix[14] -
                    matrix[5]   * matrix[2]     * matrix[15] +
                    matrix[5]   * matrix[3]     * matrix[14] +
                    matrix[13]  * matrix[2]     * matrix[7] -
                    matrix[13]  * matrix[3]     * matrix[6];

    out.matrix[6] = -matrix[0]  * matrix[6]     * matrix[15] +
                    matrix[0]   * matrix[7]     * matrix[14] +
                    matrix[4]   * matrix[2]     * matrix[15] -
                    matrix[4]   * matrix[3]     * matrix[14] -
                    matrix[12]  * matrix[2]     * matrix[7] +
                    matrix[12]  * matrix[3]     * matrix[6];

    out.matrix[10] = matrix[0]  * matrix[5]     * matrix[15] -
                     matrix[0]  * matrix[7]     * matrix[13] -
                     matrix[4]  * matrix[1]     * matrix[15] +
                     matrix[4]  * matrix[3]     * matrix[13] +
                     matrix[12] * matrix[1]     * matrix[7] -
                     matrix[12] * matrix[3]     * matrix[5];

    out.matrix[14] = -matrix[0] * matrix[5]     * matrix[14] +
                     matrix[0]  * matrix[6]     * matrix[13] +
                     matrix[4]  * matrix[1]     * matrix[14] -
                     matrix[4]  * matrix[2]     * matrix[13] -
                     matrix[12] * matrix[1]     * matrix[6] +
                     matrix[12] * matrix[2]     * matrix[5];

    out.matrix[3] = -matrix[1]  * matrix[6]     * matrix[11] +
                    matrix[1]   * matrix[7]     * matrix[10] +
                    matrix[5]   * matrix[2]     * matrix[11] -
                    matrix[5]   * matrix[3]     * matrix[10] -
                    matrix[9]   * matrix[2]     * matrix[7] +
                    matrix[9]   * matrix[3]     * matrix[6];

    out.matrix[7] = matrix[0]   * matrix[6]     * matrix[11] -
                    matrix[0]   * matrix[7]     * matrix[10] -
                    matrix[4]   * matrix[2]     * matrix[11] +
                    matrix[4]   * matrix[3]     * matrix[10] +
                    matrix[8]   * matrix[2]     * matrix[7] -
                    matrix[8]   * matrix[3]     * matrix[6];

    out.matrix[11] = -matrix[0] * matrix[5]     * matrix[11] +
                     matrix[0]  * matrix[7]     * matrix[9] +
                     matrix[4]  * matrix[1]     * matrix[11] -
                     matrix[4]  * matrix[3]     * matrix[9] -
                     matrix[8]  * matrix[1]     * matrix[7] +
                     matrix[8]  * matrix[3]     * matrix[5];

    out.matrix[15] = matrix[0]  * matrix[5]     * matrix[10] -
                     matrix[0]  * matrix[6]     * matrix[9] -
                     matrix[4]  * matrix[1]     * matrix[10] +
                     matrix[4]  * matrix[2]     * matrix[9] +
                     matrix[8]  * matrix[1]     * matrix[6] -
                     matrix[8]  * matrix[2]     * matrix[5];

    float det;
    det = matrix[0] * out.matrix[0] + matrix[1] * out.matrix[4] + matrix[2] * out.matrix[8] + matrix[3] * out.matrix[12];
    if (det == 0)
        out.init();
        return out;

    det = 1.0 / det;

    for (int i = 0; i < 16; i++)
        out.matrix[i] = out.matrix[i] * det;

    return out;
}

// Apply changes

void Matrix3D::commit() {
    glMultMatrixf(matrix);
}
