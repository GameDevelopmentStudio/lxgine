#ifndef __VECTOR2_H__
#define __VECTOR2_H__

class Vector2 {
public:
    union {
        struct {
            double x, y;
        };
        // allow array access too
        double coords[2];
    };

    Vector2(double x = 0, double y = 0);
    Vector2(const Vector2 &other);
    ~Vector2();

    // -> R2
    Vector2 operator-() const;
    // N -> R
    double &operator[](int i);
    const double &operator[](int i) const;
    // R2 -> R
    double module() const;
    // R2xR2 -> R2
    void operator-=(const Vector2 &other);
    void operator+=(const Vector2 &other);
    
    // R2 -> R2
    friend Vector2 normalizedVector(const Vector2 &v);
    // RxR2 -> R2
    friend Vector2 operator*(const float &a, const Vector2 &v);
    friend Vector2 operator*(const Vector2 &v, const float &a);
    // R2xR2 -> R
    friend double scalarDot(const Vector2 &a, const Vector2 &b);
    // R2xR2 -> R2
    friend Vector2 operator-(const Vector2 &a, const Vector2 &b);
    friend Vector2 operator+(const Vector2 &a, const Vector2 &b);
};

#endif
