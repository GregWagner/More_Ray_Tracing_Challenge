/*
* Tuple.h
 * A tuple represents an ordered list of numbers.
 * Abstraction for things like position, direction, and distance.
 *
 * Note: w = 1 is a point, w = 0 is a vector.
 *  * Adding a point (w=1) to a vector (w=0) results in a point (w=1 + 0 = 1)
 *  * Adding 2 vectors (w=0) results in a vector (w=0 + 0 = 0)
 */

#pragma once

#include <cmath>

namespace rtc {
    struct Tuple {
        static constexpr double EPSILON{1e-9};

        double x_value{};
        double y_value{};
        double z_value{};
        double w_value{}; // 1 for point, 0 for vector

        Tuple() = default;

        Tuple(double x_coord, double y_coord, double z_coord, double w_coord)
            : x_value{x_coord}, y_value{y_coord}, z_value{z_coord}, w_value{w_coord} {
        }

        static Tuple point(double x_coord, double y_coord, double z_coord) {
            return Tuple{x_coord, y_coord, z_coord, 1.0};
        }

        static Tuple vector(double x_coord, double y_coord, double z_coord) {
            return Tuple{x_coord, y_coord, z_coord, 0.0};
        }

        [[nodiscard]] bool is_point() const {
            return std::fabs(w_value - 1.0) < EPSILON;
        }

        [[nodiscard]] bool is_vector() const {
            return std::fabs(w_value) < EPSILON;
        }

        Tuple operator+(const Tuple &other) const {
            return Tuple{
                x_value + other.x_value,
                y_value + other.y_value,
                z_value + other.z_value,
                w_value + other.w_value
            };
        }

        Tuple operator-(const Tuple &other) const {
            return Tuple{
                x_value - other.x_value,
                y_value - other.y_value,
                z_value - other.z_value,
                w_value - other.w_value
            };
        }

        Tuple operator-() const {
            return Tuple{-x_value, -y_value, -z_value, -w_value};
        }

        Tuple operator*(double scalar) const {
            return Tuple{
                x_value * scalar,
                y_value * scalar,
                z_value * scalar,
                w_value * scalar
            };
        }

        Tuple operator/(double scalar) const {
            return Tuple{
                x_value / scalar,
                y_value / scalar,
                z_value / scalar,
                w_value / scalar
            };
        }

        bool operator==(const Tuple &other) const {
            return
                    std::fabs(x_value - other.x_value) < EPSILON &&
                    std::fabs(y_value - other.y_value) < EPSILON &&
                    std::fabs(z_value - other.z_value) < EPSILON &&
                    std::fabs(w_value - other.w_value) < EPSILON;
        }
    };

    inline double magnitude(const Tuple &tuple) {
        return std::sqrt(
            (tuple.x_value * tuple.x_value) +
            (tuple.y_value * tuple.y_value) +
            (tuple.z_value * tuple.z_value) +
            (tuple.w_value * tuple.w_value));
    }

    inline Tuple normalize(const Tuple &tuple) {
        const double mag = magnitude(tuple);
        return Tuple{
            tuple.x_value / mag,
            tuple.y_value / mag,
            tuple.z_value / mag,
            tuple.w_value / mag
        };
    }

    inline double dot(const Tuple &tuple_a, const Tuple &tuple_b) {
        return (tuple_a.x_value * tuple_b.x_value) +
               (tuple_a.y_value * tuple_b.y_value) +
               (tuple_a.z_value * tuple_b.z_value) +
               (tuple_a.w_value * tuple_b.w_value);
    }

    inline Tuple cross(const Tuple &tuple_a, const Tuple &tuple_b) {
        return Tuple::vector((tuple_a.y_value * tuple_b.z_value) - (tuple_a.z_value * tuple_b.y_value),
                             (tuple_a.z_value * tuple_b.x_value) - (tuple_a.x_value * tuple_b.z_value),
                             (tuple_a.x_value * tuple_b.y_value) - (tuple_a.y_value * tuple_b.x_value));
    }
} // namespace rtc
