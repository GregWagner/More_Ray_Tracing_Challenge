/*
 * color.hpp
 * A color represents an RGB color with red, green, and blue components.
 * Each component is a double value typically in the range [0, 1].
 */

#pragma once

#include <cmath>
#include <ostream>

namespace rtc {
    struct Color {
        static constexpr double EPSILON{1e-9};

        double red{};
        double green{};
        double blue{};

        Color() = default;

        constexpr Color(double r, double g, double b) : red(r), green(g), blue(b) {
        }

        [[nodiscard]] static constexpr Color rgb(double r, double g, double b) {
            return {r, g, b};
        }

        [[nodiscard]] Color operator+(const Color &other) const noexcept {
            return {red + other.red, green + other.green, blue + other.blue};
        }

        [[nodiscard]] Color operator-(const Color &other) const noexcept {
            return {red - other.red, green - other.green, blue - other.blue};
        }

        [[nodiscard]] Color operator*(double scalar) const noexcept {
            return {red * scalar, green * scalar, blue * scalar};
        }

        [[nodiscard]] Color operator*(const Color &other) const noexcept {
            return {red * other.red, green * other.green, blue * other.blue};
        }

        [[nodiscard]] Color operator/(double scalar) const {
            if (scalar == 0.0) {
                throw std::invalid_argument("Division by zero");
            }
            return {red / scalar, green / scalar, blue / scalar};
        }

        [[nodiscard]] bool operator==(const Color &other) const {
            return std::fabs(red - other.red) < EPSILON &&
                   std::fabs(green - other.green) < EPSILON &&
                   std::fabs(blue - other.blue) < EPSILON;
        }

        [[nodiscard]] bool operator!=(const Color &other) const noexcept {
            return !(*this == other);
        }

        Color &operator+=(const Color &other) noexcept {
            red += other.red;
            green += other.green;
            blue += other.blue;
            return *this;
        }

        Color &operator-=(const Color &other) noexcept {
            red -= other.red;
            green -= other.green;
            blue -= other.blue;
            return *this;
        }

        Color &operator*=(double scalar) noexcept {
            red *= scalar;
            green *= scalar;
            blue *= scalar;
            return *this;
        }

        Color &operator*=(const Color &other) noexcept {
            red *= other.red;
            green *= other.green;
            blue *= other.blue;
            return *this;
        }

        Color &operator/=(double scalar) {
            red /= scalar;
            green /= scalar;
            blue /= scalar;
            return *this;
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const Color &color) {
        os << "Color(" << color.red << ", " << color.green << ", " << color.blue << ")";
        return os;
    }
}
