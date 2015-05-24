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

// N->R Functions

template <class T>
T &Vector3<T>::operator[](int i) {
    return coords[i];
}

template <class T>
const T &Vector3<T>::operator[](int i) const {
    return coords[i];
}

// R3->R Functions

template <class T>
T Vector3<T>::module() const {
    return sqrt(scalarDot(*this, *this));
}

// R3->R3 Functions

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

// RxR3->R3 Functions

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

// R3xR3->R Functions

template <class T>
T scalarDot(const Vector3<T> &a, const Vector3<T> &b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

// R3xR3->R3 Functions

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