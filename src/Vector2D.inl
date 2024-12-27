//
// Created by Ryan Strauss on 12/9/19.
//
#include "random.h"
#include "Vector2D.h"
#include <cassert>

namespace utils {
    template<typename T>
    Vector2D<T> Vector2D<T>::operator+(const Vector2D<T>& other) const {
        return Vector2D<T>{x + other.x, y + other.y};
    }
    template<typename T>
    Vector2D<T> Vector2D<T>::operator-(const Vector2D<T> &other) const {
        return Vector2D<T>{x - other.x, y - other.y};
    }

    template<typename T>
    Vector2D<T> Vector2D<T>::operator+(T scalar) const {
        return Vector2D<T>{x + scalar, y + scalar};
    }

    template<typename T>
    Vector2D<T> Vector2D<T>::operator-(T scalar) const {
        return Vector2D<T>{x - scalar, y - scalar};
    }

    template<typename T>
    Vector2D<T> &Vector2D<T>::operator+=(const Vector2D<T> &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    template<typename T>
    Vector2D<T> &Vector2D<T>::operator-=(const Vector2D<T> &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    template<typename T>
    Vector2D<T> &Vector2D<T>::operator+=(T scalar) {
        x += scalar;
        y += scalar;
        return *this;
    }

    template<typename T>
    Vector2D<T> &Vector2D<T>::operator-=(T scalar) {
        x -= scalar;
        y -= scalar;
        return *this;
    }

    template<typename T>
    Vector2D<T> Vector2D<T>::operator*(const Vector2D<T> &other) const {
        return Vector2D<T>{x * other.x, y * other.y};
    }

    template<typename T>
    Vector2D<T> Vector2D<T>::operator*(T scalar) const {
        return Vector2D<T>{x * scalar, y * scalar};
    }

    template<typename T>
    Vector2D<T> &Vector2D<T>::operator*=(const Vector2D<T> &other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    template<typename T>
    Vector2D<T> &Vector2D<T>::operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    template<typename T>
    Vector2D<T> Vector2D<T>::operator/(const Vector2D<T> &other) const {
        assert(other.x != 0 && "Vector2::operator/ other.x cannot divide by 0");
        assert(other.y != 0 && "Vector2::operator/ other.y cannot divide by 0");
        return Vector2D<T>{x / other.x, y / other.y};
    }

    template<typename T>
    Vector2D<T> Vector2D<T>::operator/(T scalar) const {
        assert(scalar != 0 && "Vector2::operator/ scalar cannot divide by 0");
        return Vector2D<T>{x / scalar, y / scalar};
    }

    template<typename T>
    Vector2D<T> &Vector2D<T>::operator/=(const Vector2D<T> &other) {
        assert(other.x != 0 && "Vector2::operator/= other.x cannot divide by 0");
        assert(other.y != 0 && "Vector2::operator/= other.y cannot divide by 0");

        x /= other.x;
        y /= other.y;
        return *this;
    }

    template<typename T>
    Vector2D<T> &Vector2D<T>::operator/=(T scalar) {
        assert(scalar != 0 && "Vector2::operator/= scalar cannot divide by 0");

        x /= scalar;
        y /= scalar;
        return *this;
    }

    template<typename T>
    bool Vector2D<T>::operator==(const Vector2D<T> &other) const {
        return x == other.x && y == other.y;
    }

    template<typename T>
    bool Vector2D<T>::operator!=(const Vector2D<T> &other) const {
        return !operator==(other);
    }

    template<typename T>
    Vector2D<T> Vector2D<T>::operator-() const {
        return Vector2D<T>(-x, -y);
    }

    template<typename T>
    T Vector2D<T>::distance2(const Vector2D<T> &other) const {
        T dx = x - other.x;
        T dy = y - other.y;
        return dx * dx + dy * dy;
    }

    template<typename T>
    T Vector2D<T>::toroidal_distance2(const Vector2D<T> &other, T width, T height) const {
        T dx = x - other.x;
        T dy = y - other.y;

        if (dx > width / 2)
            dx = width - dx;

        if (dy > height / 2)
            dy = height - dy;

        return dx * dx + dy * dy;
    }

    template<typename T>
    T Vector2D<T>::magnitude() const {
        return sqrt(x * x + y * y);
    }

    template<typename T>
    Vector2D<T> &Vector2D<T>::normalize() {
        T mag = magnitude();
        if (mag != 0) {
            x /= mag;
            y /= mag;
        }
        return *this;
    }

    template<typename T>
    Vector2D<T> &Vector2D<T>::limit(T max) {
        T mag = magnitude();
        if (mag > max) {
            x *= max / mag;
            y *= max / mag;
        }
        return *this;
    }

    template<typename T>
    Vector2D<T> Vector2D<T>::random() {
        return Vector2D<T>{utils::random(1.0f), utils::random(1.0f)};
    }
}