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

        Color(double r, double g, double b) : red(r), green(g), blue(b) {
        }

        [[nodiscard]] static Color rgb(double r, double g, double b) {
            return Color(r, g, b);
        }

        [[nodiscard]] Color operator+(const Color &other) const {
            return Color(red + other.red, green + other.green, blue + other.blue);
        }

        [[nodiscard]] Color operator-(const Color &other) const {
            return Color(red - other.red, green - other.green, blue - other.blue);
        }

        [[nodiscard]] Color operator*(double scalar) const {
            return Color(red * scalar, green * scalar, blue * scalar);
        }

        [[nodiscard]] Color operator*(const Color &other) const {
            return Color(red * other.red, green * other.green, blue * other.blue);
        }

        [[nodiscard]] Color operator/(double scalar) const {
            return Color(red / scalar, green / scalar, blue / scalar);
        }

        [[nodiscard]] bool operator==(const Color &other) const {
            return std::fabs(red - other.red) < EPSILON &&
                   std::fabs(green - other.green) < EPSILON &&
                   std::fabs(blue - other.blue) < EPSILON;
        }

        [[nodiscard]] bool operator!=(const Color &other) const {
            return !(*this == other);
        }

        Color &operator+=(const Color &other) {
            red += other.red;
            green += other.green;
            blue += other.blue;
            return *this;
        }

        Color &operator-=(const Color &other) {
            red -= other.red;
            green -= other.green;
            blue -= other.blue;
            return *this;
        }

        Color &operator*=(double scalar) {
            red *= scalar;
            green *= scalar;
            blue *= scalar;
            return *this;
        }

        Color &operator*=(const Color &other) {
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
