/*
 * color.hpp
 * A color represents an RGB color with red, green, and blue components.
 * Each component is a double value typically in the range [0, 1].
 */

#pragma once

#include <cmath>
#include <ostream>

namespace rtc {
    // Color represents an RGB color with red, green, and blue components.
    // Used for color operations in ray tracing such as lighting calculations and pixel rendering.
    struct Color {
        static constexpr double EPSILON{1e-9}; // Tolerance for floating-point comparisons

        double red{};   // Red component [0.0, 1.0]
        double green{}; // Green component [0.0, 1.0]
        double blue{};  // Blue component [0.0, 1.0]

        // Default constructor initializes all components to zero (black)
        Color() = default;

        // Constructor to create a color from RGB components
        constexpr Color(double r, double g, double b) : red(r), green(g), blue(b) {
        }

        // Factory method to create a color from RGB components
        [[nodiscard]] static constexpr auto rgb(double r, double g, double b) -> Color {
            return {r, g, b};
        }

        // Add two colors component-wise (useful for combining light sources)
        [[nodiscard]] auto operator+(const Color &other) const noexcept -> Color {
            return {red + other.red, green + other.green, blue + other.blue};
        }

        // Subtract two colors component-wise
        [[nodiscard]] auto operator-(const Color &other) const noexcept -> Color {
            return {red - other.red, green - other.green, blue - other.blue};
        }

        // Multiply color by a scalar (scales brightness)
        [[nodiscard]] auto operator*(double scalar) const noexcept -> Color {
            return {red * scalar, green * scalar, blue * scalar};
        }

        // Multiply two colors component-wise (Hadamard product)
        // Useful for filtering colors through surfaces
        [[nodiscard]] auto operator*(const Color &other) const noexcept -> Color {
            return {red * other.red, green * other.green, blue * other.blue};
        }

        // Divide color by a scalar
        // Throws if scalar is zero (division by zero)
        [[nodiscard]] auto operator/(double scalar) const -> Color {
            if (scalar == 0.0) {
                throw std::invalid_argument("Division by zero");
            }
            return {red / scalar, green / scalar, blue / scalar};
        }

        // Equality comparison using epsilon tolerance for floating-point values
        [[nodiscard]] auto operator==(const Color &other) const -> bool {
            return std::fabs(red - other.red) < EPSILON &&
                   std::fabs(green - other.green) < EPSILON &&
                   std::fabs(blue - other.blue) < EPSILON;
        }

        // Inequality comparison
        [[nodiscard]] auto operator!=(const Color &other) const noexcept -> bool {
            return !(*this == other);
        }

        // Compound assignment addition
        auto operator+=(const Color &other) noexcept -> Color & {
            red += other.red;
            green += other.green;
            blue += other.blue;
            return *this;
        }

        // Compound assignment subtraction
        auto operator-=(const Color &other) noexcept -> Color & {
            red -= other.red;
            green -= other.green;
            blue -= other.blue;
            return *this;
        }

        // Compound assignment scalar multiplication
        auto operator*=(double scalar) noexcept -> Color & {
            red *= scalar;
            green *= scalar;
            blue *= scalar;
            return *this;
        }

        // Compound assignment color multiplication
        auto operator*=(const Color &other) noexcept -> Color & {
            red *= other.red;
            green *= other.green;
            blue *= other.blue;
            return *this;
        }

        // Compound assignment scalar division
        auto operator/=(double scalar) -> Color & {
            red /= scalar;
            green /= scalar;
            blue /= scalar;
            return *this;
        }
    };

    auto operator<<(std::ostream &os, const Color &color) -> std::ostream &;
}
