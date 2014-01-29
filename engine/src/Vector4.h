#ifndef __VECTOR4_H__
#define __VECTOR4_H__

template <class T> class Vector2;
template <class T> class Vector3;

template <class T>
class Vector4 {
public:
    union {
        struct {
            T x, y, z, v;
        };
        // allow array access too
        T coords[4];
    };
    /* int v; */

    Vector4(T x = 0, T y = 0, T z = 0, T v = 1);
    Vector4(const Vector4 &other);
    explicit Vector4(const Vector3<T> &other, const T v3);
    explicit Vector4(const Vector2<T> &other, const T v2, const T v3);
    ~Vector4();

    // -> R3
    Vector4<T> operator-() const;
    // N -> R
    T &operator[](int i);
    const T &operator[](int i) const;
    // R3 -> R
    T module() const;
    // R3xR3 -> R3
    void operator-=(const Vector4<T> &other);
    void operator+=(const Vector4<T> &other);
};

// R3 -> R3
template <class T> Vector4<T> normalizedVector(const Vector4<T> &v);
// RxR3 -> R3
template <class T> Vector4<T> operator*(const float &a, const Vector4<T> &v);
template <class T> Vector4<T> operator*(const Vector4<T> &v, const T &a);
// R3xR3 -> R
template <class T> T scalarDot(const Vector4<T> &a, const Vector4<T> &b);
// R3xR3 -> R3
template <class T> Vector4<T> operator-(const Vector4<T> &a, const Vector4<T> &b);
template <class T> Vector4<T> operator+(const Vector4<T> &a, const Vector4<T> &b);
template <class T> Vector4<T> crossProduct(const Vector4<T> &a, const Vector4<T> &b);

typedef Vector4<float> Vector4f;
typedef Vector4<double> Vector4d;

/*******************
 * Implementation
 ******************/

template <class T>
Vector4<T>::Vector4(T x, T y, T z, T v) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->v = v;
}

template <class T>
Vector4<T>::Vector4(const Vector4<T> &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    v = other.v;
}

template <class T>
Vector4<T>::Vector4(const Vector3<T> &other, const T v3) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->v = v3;
}

template <class T>
Vector4<T>::Vector4(const Vector2<T> &other, const T v2, const T v3) {
    this->x = other.x;
    this->y = other.y;
    this->z = v2;
    this->v = v3;
}

template <class T>
Vector4<T>::~Vector4() {
}

// N->R Functions

template <class T>
T &Vector4<T>::operator[](int i) {
    return coords[i];
}

template <class T>
const T &Vector4<T>::operator[](int i) const {
    return coords[i];
}

// R3->R Functions

template <class T>
T Vector4<T>::module() const {
    return sqrt(scalarDot(*this, *this));
}

// R3->R3 Functions

template <class T>
Vector4<T> Vector4<T>::operator-() const {
    return Vector4(-x, -y, -z, -v);
}

template <class T>
Vector4<T> normalizedVector(const Vector4<T> &v) {
    T mod = v.module();
    return Vector4<T>(v.x / mod,
                      v.y / mod,
                      v.z / mod,
                      v.v / mod);
}

// RxR3->R3 Functions

template <class T>
Vector4<T> operator*(const float &a, const Vector4<T> &v) {
    return Vector4<T>(a * v.x,
                      a * v.y,
                      a * v.z,
                      a * v.v);
}

template <class T>
Vector4<T> operator*(const Vector4<T> &v, const float &a) {
    return Vector4<T>(v.x * a,
                      v.y * a,
                      v.z * a,
                      v.v * a);
}

// R3xR3->R Functions

template <class T>
T scalarDot(const Vector4<T> &a, const Vector4<T> &b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

// R3xR3->R3 Functions

template <class T>
Vector4<T> operator-(const Vector4<T> &a, const Vector4<T> &b) {
    return Vector4<T>(a.x - b.x,
                      a.y - b.y,
                      a.z - b.z,
                      a.v - b.v);
}

template <class T>
Vector4<T> operator+(const Vector4<T> &a, const Vector4<T> &b) {
    return Vector4<T>(a.x + b.x,
                      a.y + b.y,
                      a.z + b.z,
                      a.v + b.v);
}

template <class T>
void Vector4<T>::operator-=(const Vector4<T> &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    v -= other.v;
}

template <class T>
void Vector4<T>::operator+=(const Vector4<T> &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    v += other.v;
}

template <class T>
Vector4<T> crossProduct(const Vector4<T> &a, const Vector4<T> &b) {
    return Vector4<T>(a.y*b.z - a.z*b.y,
                      a.z*b.x - a.x*b.z,
                      a.x*b.y - a.y*b.x,
                      0.0); // CHECK?
}



#endif
