template <class T>
Vector4<T>::Vector4(const Vector4<T> &other) {
    x = other.getX();
    y = other.getY();
    z = other.getZ();
    w = other.getW();
}

template <class T>
Vector4<T>::Vector4(const Vector3<T> &other, const T v3) {
    this->x = other.getX();
    this->y = other.getY();
    this->z = other.getZ();
    this->w = v3;
}

template <class T>
Vector4<T>::Vector4(const Vector2<T> &other, const T z, const T w) {
    this->x = other.getX();
    this->y = other.getY();
    this->z = z;
    this->w = w;
}

template <class T>
Vector4<T>::Vector4(T x, T y, T z, T w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

template <class T>
Vector4<T>::~Vector4() {
}

// Getters

template <class T>
const T& Vector4<T>::getX() const {
    return x;
}

template <class T>
const T& Vector4<T>::getY() const {
    return y;
}

template <class T>
const T& Vector4<T>::getZ() const {
    return z;
}

template <class T>
const T& Vector4<T>::getW() const {
    return w;
}

template <class T>
T& Vector4<T>::getX() {
    return x;
}

template <class T>
T& Vector4<T>::getY() {
    return y;
}

template <class T>
T& Vector4<T>::getZ() {
    return z;
}

template <class T>
T& Vector4<T>::getW() {
    return w;
}

template <class T>
void Vector4<T>::setX(const T& v) {
    x = v;
}

template <class T>
void Vector4<T>::setY(const T& v) {
    y = v;
}

template <class T>
void Vector4<T>::setZ(const T& v) {
    z = v;
}

template <class T>
void Vector4<T>::setW(const T& v) {
    w = v;
}

template <class T>
const Vector2<T>& Vector4<T>::getXY() const {
    return (*reinterpret_cast<const Vector2<T>*>(this));
}

template <class T>
const Vector3<T>& Vector4<T>::getXYZ() const {
    return (*reinterpret_cast<const Vector3<T>*>(this));
}

template <class T>
Vector2<T>& Vector4<T>::getXY() {
    return (*reinterpret_cast<Vector2<T>*>(this));
}

template <class T>
Vector3<T>& Vector4<T>::getXYZ() {
    return (*reinterpret_cast<Vector3<T>*>(this));
}

// N->R Functions

template <class T>
T& Vector4<T>::operator[](int i) {
    return coords[i];
}

template <class T>
const T& Vector4<T>::operator[](int i) const {
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
    return Vector4(-x, -y, -z, -w);
}

template <class T>
Vector4<T> normalizedVector(const Vector4<T> &v) {
    T mod = v.module();
    return Vector4<T>(v.getX() / mod,
                      v.getY() / mod,
                      v.getZ() / mod,
                      v.getW() / mod);
}

// RxR3->R3 Functions

template <class T>
Vector4<T> operator*(const T &a, const Vector4<T> &v) {
    return Vector4<T>(a * v.getX(),
                      a * v.getY(),
                      a * v.getZ(),
                      a * v.getW());
}

template <class T>
Vector4<T> operator*(const Vector4<T> &v, const T &a) {
    return Vector4<T>(v.getX() * a,
                      v.getY() * a,
                      v.getZ() * a,
                      v.getW() * a);
}

// R3xR3->R Functions

template <class T>
T scalarDot(const Vector4<T> &a, const Vector4<T>& b) {
    return scalarDot(*reinterpret_cast<const Vector3<T>*>(&a), *reinterpret_cast<const Vector3<T>*>(&b));
}

// R3xR3->R3 Functions

template <class T>
Vector4<T> operator-(const Vector4<T> &a, const Vector4<T> &b) {
    return Vector4<T>(a.getX() - b.getX(),
                      a.getY() - b.getY(),
                      a.getZ() - b.getZ(),
                      a.getW() - b.getW());
}

template <class T>
Vector4<T> operator+(const Vector4<T> &a, const Vector4<T> &b) {
    return Vector4<T>(a.getX() + b.getX(),
                      a.getY() + b.getY(),
                      a.getZ() + b.getZ(),
                      a.getW() + b.getW());
}

template <class T>
void Vector4<T>::operator-=(const Vector4<T> &other) {
    x -= other.getX();
    y -= other.getY();
    z -= other.getZ();
    w -= other.getW();
}

template <class T>
void Vector4<T>::operator+=(const Vector4<T> &other) {
    x += other.getX();
    y += other.getY();
    z += other.getZ();
    w += other.getW();
}

template <class T>
Vector4<T> crossProduct(const Vector4<T> &a, const Vector4<T> &b) {
    return Vector4<T>(a.getY()*b.getZ() - a.getZ()*b.getY(),
                      a.getZ()*b.getX() - a.getX()*b.getZ(),
                      a.getX()*b.getY() - a.getY()*b.getX(),
                      0.0); // CHECK?
}