//
// Created by Ryan Strauss on 12/9/19.
//

#ifndef BOIDS_VECTOR2D_H
#define BOIDS_VECTOR2D_H

#include <cmath>

namespace utils {
    template <typename T>
    class Vector2D {
    public:
        T x{}, y{};

        // Constructors
        Vector2D(T x = 0, T y = 0): x{x}, y{y} {}
        static Vector2D random();

        // Operators
        Vector2D operator+(const Vector2D& other) const;
        Vector2D operator+(T scalar) const;

        Vector2D operator-(const Vector2D& other) const;
        Vector2D operator-(T scalar) const;

        Vector2D& operator+=(const Vector2D& other);
        Vector2D& operator+=(T scalar);

        Vector2D& operator-=(const Vector2D& other);
        Vector2D& operator-=(T scalar);

        Vector2D operator*(const Vector2D& other) const;
        Vector2D operator*(T scalar) const;

        Vector2D& operator*=(const Vector2D& other);
        Vector2D& operator*=(T scalar);

        Vector2D operator/(const Vector2D& other) const;
        Vector2D operator/(T scalar) const;

        Vector2D& operator/=(const Vector2D& other);
        Vector2D& operator/=(T scalar);

        bool operator==(const Vector2D& other) const;
        bool operator!=(const Vector2D& other) const;
        Vector2D operator-() const;

        // Methods
        T distance2(const Vector2D &other) const;
        T distance(const Vector2D &other) const {
            return std::sqrt(distance2(other));
        }

        T toroidal_distance2(const Vector2D &other, T width, T height) const;
        T toroidal_distance(const Vector2D &other, T width, T height) const {
            return std::sqrt(toroidal_distance2(other, width, height));
        }

        T magnitude() const;
        Vector2D &normalize();
        Vector2D &limit(T max);
    };

}

#include "Vector2D.inl"

#endif //BOIDS_VECTOR2D_H
