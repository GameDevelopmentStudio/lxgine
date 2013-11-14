#ifndef __VECTOR3_H__
#define __VECTOR3_H__

template <class T> class Vector2;

template <class T>
class Vector3 {
public:
    union {
        struct {
            T x, y, z;
        };
        // allow array access too
        T coords[3];
    };

    Vector3<T>(T x = 0, T y = 0, T z = 0);
    Vector3<T>(const Vector3<T> &other);
    explicit Vector3<T>(const Vector2<T> &other, T v2);
    ~Vector3<T>();

    // -> R3
    Vector3<T> operator-() const;
    // N -> R
    T &operator[](int i);
    const T &operator[](int i) const;
    // R3 -> R
    T module() const;
    // R3xR3 -> R3
    void operator-=(const Vector3<T> &other);
    void operator+=(const Vector3<T> &other);
};

// R3 -> R3
template <class T> Vector3<T> normalizedVector(const Vector3<T> &v);
// RxR3 -> R3
template <class T> Vector3<T> operator*(const float &a, const Vector3<T> &v);
template <class T> Vector3<T> operator*(const Vector3<T> &v, const float &a);
// R3xR3 -> R
template <class T> T scalarDot(const Vector3<T> &a, const Vector3<T> &b);
// R3xR3 -> R3
template <class T> Vector3<T> operator-(const Vector3<T> &a, const Vector3<T> &b);
template <class T> Vector3<T> operator+(const Vector3<T> &a, const Vector3<T> &b);
template <class T> Vector3<T> crossProduct(const Vector3<T> &a, const Vector3<T> &b);

typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;

/*******************
 * Implementation
 ******************/

template <class T>
Vector3<T>::Vector3(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template <class T>
Vector3<T>::Vector3(const Vector3<T> &other) {
    x = other.x;
    y = other.y;
    z = other.z;
}

template <class T>
Vector3<T>::Vector3(const Vector2<T> &other, const T v2) {
    this->x = other.x;
    this->y = other.y;
    this->z = v2;
}

template <class T>
Vector3<T>::~Vector3() {
}

#pragma mark - N->R Functions

template <class T>
T &Vector3<T>::operator[](int i) {
    return coords[i];
}

template <class T>
const T &Vector3<T>::operator[](int i) const {
    return coords[i];
}

#pragma mark - R3->R Functions

template <class T>
T Vector3<T>::module() const {
    return sqrt(scalarDot(*this, *this));
}

#pragma mark - R3->R3 Functions

template <class T>
Vector3<T> Vector3<T>::operator-() const {
    return Vector3<T>(-x, -y, -z);
}

template <class T>
Vector3<T> normalizedVector(const Vector3<T> &v) {
    T mod = v.module();
    return Vector3<T>(v.x / mod,
                      v.y / mod,
                      v.z / mod);
}

#pragma mark - RxR3->R3 Functions

template <class T>
Vector3<T> operator*(const float &a, const Vector3<T> &v) {
    return Vector3<T>(a * v.x,
                      a * v.y,
                      a * v.z);
}

template <class T>
Vector3<T> operator*(const Vector3<T> &v, const float &a) {
    return Vector3<T>(v.x * a,
                      v.y * a,
                      v.z * a);
}

#pragma mark - R3xR3->R Functions

template <class T>
T scalarDot(const Vector3<T> &a, const Vector3<T> &b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

#pragma mark - R3xR3->R3 Functions

template <class T>
Vector3<T> operator-(const Vector3<T> &a, const Vector3<T> &b) {
    return Vector3<T>(a.x - b.x,
                      a.y - b.y,
                      a.z - b.z);
}

template <class T>
Vector3<T> operator+(const Vector3<T> &a, const Vector3<T> &b) {
    return Vector3<T>(a.x + b.x,
                      a.y + b.y,
                      a.z + b.z);
}

template <class T>
void Vector3<T>::operator-=(const Vector3<T> &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
}

template <class T>
void Vector3<T>::operator+=(const Vector3<T> &other) {
    x += other.x;
    y += other.y;
    z += other.z;
}

template <class T>
Vector3<T> crossProduct(const Vector3<T> &a, const Vector3<T> &b) {
    return Vector3<T>(a.y*b.z - a.z*b.y,
                      a.z*b.x - a.x*b.z,
                      a.x*b.y - a.y*b.x);
}



#endif
