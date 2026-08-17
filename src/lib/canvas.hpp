#pragma once

#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

#include "color.hpp"

namespace rtc {
    class Canvas {
    public:
        Canvas(int width, int height)
            : Canvas(width, height, Color(0.0, 0.0, 0.0)) {
        }

        Canvas(int width, int height, Color default_color)
            : width_(width), height_(height),
              pixels_(static_cast<std::size_t>(width) * static_cast<std::size_t>(height), default_color) {
            if (width <= 0 || height <= 0) {
                throw std::invalid_argument("Canvas dimensions must be positive.");
            }
        }

        [[nodiscard]] int width() const noexcept { return width_; }
        [[nodiscard]] int height() const noexcept { return height_; }

        [[nodiscard]] Color pixel_at(int x_value, int y_value) const {
            bounds_check(x_value, y_value);
            return pixels_[to_index(x_value, y_value)];
        }

        void write_pixel(int x_value, int y_value, const Color &color) {
            bounds_check(x_value, y_value);
            pixels_[to_index(x_value, y_value)] = color;
        }

    private:
        int width_;
        int height_;
        std::vector<Color> pixels_;

        [[nodiscard]] std::size_t to_index(int x_value, int y_value) const noexcept {
            return static_cast<std::size_t>((y_value * width_) + x_value);
        }

        void bounds_check(int x_value, int y_value) const {
            if (x_value < 0 || x_value >= width_ || y_value < 0 || y_value >= height_) {
                throw std::out_of_range("Pixel coordinates out of canvas bounds.");
            }
        }
    };

    inline std::string canvas_to_ppm(const Canvas &c) {
        std::ostringstream oss;
        oss << "P3\n"
                << c.width() << " " << c.height() << "\n"
                << "255\n";

        auto scale_color = [](double value) -> int {
            // clamp color values to [0.0, 1.0]
            value = std::clamp(value, 0.0, 1.0);
            // scales to [0, 255] and rounds to nearest integer
            return static_cast<int>(std::round(value * 255));
        };

        size_t line_length{};
        for (int y = 0; y < c.height(); ++y) {
            for (int x = 0; x < c.width(); ++x) {
                Color pixel = c.pixel_at(x, y);
                int r = scale_color(pixel.red);
                int g = scale_color(pixel.green);
                int b = scale_color(pixel.blue);

                std::string r_str = std::to_string(r);
                std::string g_str = std::to_string(g);
                std::string b_str = std::to_string(b);

                for (const auto &str : {r_str, g_str, b_str}) {
                    if (line_length > 0) {
                        if (line_length + 1 + str.length() > 70) {
                            oss << "\n";
                            line_length = 0;
                        } else {
                            oss << " ";
                            line_length++;
                        }
                    }
                    oss << str;
                    line_length += str.length();
                }
            }
            oss << "\n";
            line_length = 0;
        }
        return oss.str();
    }
} // namespace rtc
