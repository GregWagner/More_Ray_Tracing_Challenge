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

        [[nodiscard]] static constexpr auto rgb(double r, double g, double b) -> Color {
            return {r, g, b};
        }

        [[nodiscard]] auto operator+(const Color &other) const noexcept -> Color {
            return {red + other.red, green + other.green, blue + other.blue};
        }

        [[nodiscard]] auto operator-(const Color &other) const noexcept -> Color {
            return {red - other.red, green - other.green, blue - other.blue};
        }

        [[nodiscard]] auto operator*(double scalar) const noexcept -> Color {
            return {red * scalar, green * scalar, blue * scalar};
        }

        [[nodiscard]] auto operator*(const Color &other) const noexcept -> Color {
            return {red * other.red, green * other.green, blue * other.blue};
        }

        [[nodiscard]] auto operator/(double scalar) const -> Color {
            if (scalar == 0.0) {
                throw std::invalid_argument("Division by zero");
            }
            return {red / scalar, green / scalar, blue / scalar};
        }

        [[nodiscard]] auto operator==(const Color &other) const -> bool {
            return std::fabs(red - other.red) < EPSILON &&
                   std::fabs(green - other.green) < EPSILON &&
                   std::fabs(blue - other.blue) < EPSILON;
        }

        [[nodiscard]] auto operator!=(const Color &other) const noexcept -> bool {
            return !(*this == other);
        }

        auto operator+=(const Color &other) noexcept -> Color & {
            red += other.red;
            green += other.green;
            blue += other.blue;
            return *this;
        }

        auto operator-=(const Color &other) noexcept -> Color & {
            red -= other.red;
            green -= other.green;
            blue -= other.blue;
            return *this;
        }

        auto operator*=(double scalar) noexcept -> Color & {
            red *= scalar;
            green *= scalar;
            blue *= scalar;
            return *this;
        }

        auto operator*=(const Color &other) noexcept -> Color & {
            red *= other.red;
            green *= other.green;
            blue *= other.blue;
            return *this;
        }

        auto operator/=(double scalar) -> Color & {
            red /= scalar;
            green /= scalar;
            blue /= scalar;
            return *this;
        }
    };

    auto operator<<(std::ostream &os, const Color &color) -> std::ostream &;
}
