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
#include <ostream>
#include <stdexcept>

namespace rtc {
    // Tuple represents a 4D vector used for geometric calculations in ray tracing.
    // The w component distinguishes between points (w=1) and vectors (w=0).
    // This unified representation allows for consistent arithmetic operations.
    struct Tuple {
        static constexpr double EPSILON{1e-9}; // Tolerance for floating-point comparisons

        double x_value{}; // X coordinate
        double y_value{}; // Y coordinate
        double z_value{}; // Z coordinate
        double w_value{}; // W component: 1 for points, 0 for vectors

        // Default constructor initializes all components to zero
        Tuple() = default;

        // Constructor for creating a tuple with explicit coordinates
        constexpr Tuple(double x_coord, double y_coord, double z_coord, double w_coord)
            : x_value{x_coord}, y_value{y_coord}, z_value{z_coord}, w_value{w_coord} {
        }

        // Factory method to create a point (w=1)
        // Points represent positions in 3D space
        static constexpr auto point(double x_coord, double y_coord, double z_coord) -> Tuple {
            return Tuple{x_coord, y_coord, z_coord, 1.0};
        }

        // Factory method to create a vector (w=0)
        // Vectors represent directions and distances in 3D space
        static constexpr auto vector(double x_coord, double y_coord, double z_coord) -> Tuple {
            return Tuple{x_coord, y_coord, z_coord, 0.0};
        }

        // Check if this tuple represents a point (w ≈ 1)
        [[nodiscard]] auto is_point() const -> bool {
            return std::fabs(w_value - 1.0) < EPSILON;
        }

        // Check if this tuple represents a vector (w ≈ 0)
        [[nodiscard]] auto is_vector() const -> bool {
            return std::fabs(w_value) < EPSILON;
        }

        // Addition: adds two tuples component-wise
        // Point + Vector = Point (moving a point by a direction)
        // Vector + Vector = Vector (combining directions)
        auto operator+(const Tuple &other) const noexcept -> Tuple {
            return Tuple{
                x_value + other.x_value,
                y_value + other.y_value,
                z_value + other.z_value,
                w_value + other.w_value
            };
        }

        // Subtraction: subtracts two tuples component-wise
        // Point - Point = Vector (direction from one point to another)
        // Point - Vector = Point (moving a point opposite to a direction)
        // Vector - Vector = Vector (difference between directions)
        auto operator-(const Tuple &other) const noexcept -> Tuple {
            return Tuple{
                x_value - other.x_value,
                y_value - other.y_value,
                z_value - other.z_value,
                w_value - other.w_value
            };
        }

        // Negation: returns a tuple with all components negated
        // Useful for getting the opposite direction of a vector
        auto operator-() const noexcept -> Tuple {
            return Tuple{-x_value, -y_value, -z_value, -w_value};
        }

        // Scalar multiplication: multiplies all components by a scalar
        // Scales the length of a vector or scales a point's position
        auto operator*(double scalar) const noexcept -> Tuple {
            return Tuple{
                x_value * scalar,
                y_value * scalar,
                z_value * scalar,
                w_value * scalar
            };
        }

        // Scalar division: divides all components by a scalar
        // Throws if scalar is zero (division by zero)
        auto operator/(double scalar) const -> Tuple {
            if (std::fabs(scalar) < EPSILON) {
                throw std::invalid_argument("Division by zero");
            }
            return Tuple{
                x_value / scalar,
                y_value / scalar,
                z_value / scalar,
                w_value / scalar
            };
        }

        // Equality comparison using epsilon tolerance for floating-point values
        [[nodiscard]] auto operator==(const Tuple &other) const -> bool {
            return
                    std::fabs(x_value - other.x_value) < EPSILON &&
                    std::fabs(y_value - other.y_value) < EPSILON &&
                    std::fabs(z_value - other.z_value) < EPSILON &&
                    std::fabs(w_value - other.w_value) < EPSILON;
        }

        // Inequality comparison
        [[nodiscard]] auto operator!=(const Tuple &other) const noexcept -> bool {
            return !(*this == other);
        }

        // Compound assignment addition
        auto operator+=(const Tuple &other) noexcept -> Tuple & {
            x_value += other.x_value;
            y_value += other.y_value;
            z_value += other.z_value;
            w_value += other.w_value;
            return *this;
        }

        // Compound assignment subtraction
        auto operator-=(const Tuple &other) noexcept -> Tuple & {
            x_value -= other.x_value;
            y_value -= other.y_value;
            z_value -= other.z_value;
            w_value -= other.w_value;
            return *this;
        }

        // Compound assignment scalar multiplication
        auto operator*=(double scalar) noexcept -> Tuple & {
            x_value *= scalar;
            y_value *= scalar;
            z_value *= scalar;
            w_value *= scalar;
            return *this;
        }

        // Compound assignment scalar division
        auto operator/=(double scalar) -> Tuple & {
            x_value /= scalar;
            y_value /= scalar;
            z_value /= scalar;
            w_value /= scalar;
            return *this;
        }
    };

    // Calculate the magnitude (length) of a tuple
    // Uses the Euclidean distance formula: sqrt(x² + y² + z² + w²)
    auto magnitude(const Tuple &tuple) noexcept -> double;

    // Normalize a tuple to unit length (magnitude = 1)
    // Divides each component by the tuple's magnitude
    // Throws if the tuple has zero magnitude (cannot normalize zero vector)
    auto normalize(const Tuple &tuple) -> Tuple;

    // Calculate the dot product of two tuples
    // Returns a scalar value: sum of component-wise products
    // Useful for calculating angles between vectors (dot = |a||b|cos(θ))
    auto dot(const Tuple &tuple_a, const Tuple &tuple_b) noexcept -> double;

    // Calculate the cross product of two tuples (3D only)
    // Returns a vector perpendicular to both input vectors
    // The result is always a vector (w=0)
    // Formula: a × b = (ay*bz - az*by, az*bx - ax*bz, ax*by - ay*bx)
    auto cross(const Tuple &tuple_a, const Tuple &tuple_b) noexcept -> Tuple;

    // Stream output operator for debugging and logging
    // Outputs tuple in format: Tuple(x, y, z, w)
    auto operator<<(std::ostream &os, const Tuple &tuple) -> std::ostream &;
} // namespace rtc
