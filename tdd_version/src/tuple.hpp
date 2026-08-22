/*
 * tuple.hpp
 * A tuple represents an ordered list of numbers.
 * Abstraction for things like position, direction, and distance.
 *
 * Note: w = 1 is a point, w = 0 is a vector.
 *  Adding a point (w=1) to a vector (w=0) results in a point (w=1 + 0 = 1)
 *  Adding 2 vectors (w=0) results in a vector (w=0 + 0 = 0)
 */

/*
 * Possible improvements:
 * Add division by zero check in operator / and normalize
 */

#pragma once

#include <cmath>

namespace rtc {
    // Tuple represents a 4D vector used for geometric calculations in ray tracing.
    // The w component distinguishes between points (w=1) and vectors (w=0).
    // This unified representation allows for consistent arithmetic operations.
    struct Tuple {
        double x{}; // X coordinate
        double y{}; // Y coordinate
        double z{}; // Z coordinate
        double w{}; // W component: 1 for points, 0 for vectors

        Tuple(double x_value, double y_value, double z_value, double w_value)
            : x{x_value}, y{y_value}, z{z_value}, w{w_value} {
        }

        auto is_point() -> bool { return w == 1.0; }
        auto is_vector() -> bool { return w == 0.0; }

        Tuple operator+(Tuple other) {
            return Tuple(x + other.x, y + other.y, z + other.z, w + other.w);
        }

        Tuple operator-(Tuple other) {
            return Tuple(x - other.x, y - other.y, z - other.z, w - other.w);
        }

        Tuple operator-() {
            return Tuple(-x, -y, -z, -w);
        }

        Tuple operator*(double scalar) {
            return Tuple(x * scalar, y * scalar, z * scalar, w * scalar);
        }

        Tuple operator/(double scalar) {
            return Tuple(x / scalar, y / scalar, z / scalar, w / scalar);
        }
    };

    Tuple point(double x, double y, double z) {
        return Tuple(x, y, z, 1.0);
    }

    Tuple vector(double x, double y, double z) {
        return Tuple(x, y, z, 0.0);
    }

    // 1 * 1 + 2 * 2 + 3 * 3 = 14
    double magnitude(Tuple t) {
        return std::sqrt(t.x * t.x + t.y * t.y + t.z * t.z);
    }

    Tuple normalize(Tuple t) {
        return Tuple(t.x / magnitude(t), t.y / magnitude(t), t.z / magnitude(t), t.w);
    }

    double dot(Tuple a, Tuple b) {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    Tuple cross(Tuple a, Tuple b) {
        return Tuple(a.y * b.z - a.z * b.y,
                     a.z * b.x - a.x * b.z,
                     a.x * b.y - a.y * b.x,
                     0.0);
    }
} // namespace rtc
