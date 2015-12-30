template <class T>
Vector2<T>::Vector2(T x, T y) {
    this->x = x;
    this->y = y;
}

template <class T>
Vector2<T>::Vector2(const Vector2<T> &other) {
    x = other.x;
    y = other.y;
}

template <class T>
Vector2<T>::~Vector2() {
}

// N->R Functions

template <class T>
T &Vector2<T>::operator[](int i) {
    return coords[i];
}

template <class T>
const T &Vector2<T>::operator[](int i) const {
    return coords[i];
}

// R2->R Functions

template <class T>
T Vector2<T>::module() const {
    return sqrt(scalarDot(*this, *this));
}

// R2->R2 Functions

template <class T>
Vector2<T> Vector2<T>::operator-() const {
    return Vector2(-x, -y);
}

template <class T>
Vector2<T> normalizedVector(const Vector2<T> &v) {
    T mod = v.module();
    return Vector2<T>(v.x / mod,
                      v.y / mod);
}

// RxR2->R2 Functions

template <class T>
Vector2<T> operator*(const T &a, const Vector2<T> &v) {
    return Vector2<T>(a * v.x,
                      a * v.y);
}

template <class T>
Vector2<T> operator*(const Vector2<T> &v, const T &a) {
    return Vector2<T>(v.x * a,
                      v.y * a);
}

template <class T>
Vector2<T> operator/(const Vector2<T> &v, const T &a) {
    return Vector2<T>(v.x / a,
                      v.y / a);
}

// R2xR2->R Functions

template <class T>
T scalarDot(const Vector2<T> &a, const Vector2<T> &b) {
    return a.x*b.x + a.y*b.y;
}

// R2xR2->R2 Functions

template <class T>
Vector2<T> operator-(const Vector2<T> &a, const Vector2<T> &b) {
    return Vector2<T>(a.x - b.x,
                      a.y - b.y);
}

template <class T>
Vector2<T> operator+(const Vector2<T> &a, const Vector2<T> &b) {
    return Vector2<T>(a.x + b.x,
                      a.y + b.y);
}

template <class T>
void Vector2<T>::operator-=(const Vector2<T> &other) {
    x -= other.x;
    y -= other.y;
}

template <class T>
void Vector2<T>::operator+=(const Vector2<T> &other) {
    x += other.x;
    y += other.y;
}