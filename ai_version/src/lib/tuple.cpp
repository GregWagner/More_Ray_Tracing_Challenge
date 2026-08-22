#include "tuple.hpp"

#include <cmath>
#include <stdexcept>

namespace rtc {
    // Calculate the magnitude (length) of a tuple
    // Uses the Euclidean distance formula: sqrt(x² + y² + z² + w²)
    auto magnitude(const Tuple &tuple) noexcept -> double {
        return std::sqrt(
            (tuple.x_value * tuple.x_value) +
            (tuple.y_value * tuple.y_value) +
            (tuple.z_value * tuple.z_value) +
            (tuple.w_value * tuple.w_value));
    }

    // Normalize a tuple to unit length (magnitude = 1)
    // Divides each component by the tuple's magnitude
    // Throws if the tuple has zero magnitude (cannot normalize zero vector)
    auto normalize(const Tuple &tuple) -> Tuple {
        const double mag = magnitude(tuple);
        if (std::fabs(mag) < Tuple::EPSILON) {
            throw std::invalid_argument("Cannot normalize zero vector");
        }
        return Tuple{
            tuple.x_value / mag,
            tuple.y_value / mag,
            tuple.z_value / mag,
            tuple.w_value / mag
        };
    }

    // Calculate the dot product of two tuples
    // Returns a scalar value: sum of component-wise products
    // Useful for calculating angles between vectors (dot = |a||b|cos(θ))
    auto dot(const Tuple &tuple_a, const Tuple &tuple_b) noexcept -> double {
        return (tuple_a.x_value * tuple_b.x_value) +
               (tuple_a.y_value * tuple_b.y_value) +
               (tuple_a.z_value * tuple_b.z_value) +
               (tuple_a.w_value * tuple_b.w_value);
    }

    // Calculate the cross product of two tuples (3D only)
    // Returns a vector perpendicular to both input vectors
    // The result is always a vector (w=0)
    // Formula: a × b = (ay*bz - az*by, az*bx - ax*bz, ax*by - ay*bx)
    auto cross(const Tuple &tuple_a, const Tuple &tuple_b) noexcept -> Tuple {
        return Tuple::vector((tuple_a.y_value * tuple_b.z_value) - (tuple_a.z_value * tuple_b.y_value),
                             (tuple_a.z_value * tuple_b.x_value) - (tuple_a.x_value * tuple_b.z_value),
                             (tuple_a.x_value * tuple_b.y_value) - (tuple_a.y_value * tuple_b.x_value));
    }

    // Stream output operator for debugging and logging
    // Outputs tuple in format: Tuple(x, y, z, w)
    auto operator<<(std::ostream &os, const Tuple &tuple) -> std::ostream & {
        os << "Tuple(" << tuple.x_value << ", " << tuple.y_value << ", "
                << tuple.z_value << ", " << tuple.w_value << ")";
        return os;
    }
} // namespace rtc
