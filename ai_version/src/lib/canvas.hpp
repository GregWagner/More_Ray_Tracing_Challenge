#pragma once

#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

#include "color.hpp"

namespace rtc {
    // Canvas represents a 2D grid of pixels for rendering images.
    // Stores color data in row-major order and supports writing pixels and exporting to PPM format.
    class Canvas {
    public:
        // Create a canvas with specified dimensions, initialized to black
        Canvas(int width, int height)
            : Canvas(width, height, Color(0.0, 0.0, 0.0)) {
        }

        // Create a canvas with specified dimensions and default color
        Canvas(int width, int height, Color default_color)
            : width_(width), height_(height),
              pixels_(static_cast<std::size_t>(width) * static_cast<std::size_t>(height), default_color) {
            if (width <= 0 || height <= 0) {
                throw std::invalid_argument("Canvas dimensions must be positive.");
            }
        }

        // Get the width of the canvas in pixels
        [[nodiscard]] auto width() const noexcept -> int { return width_; }

        // Get the height of the canvas in pixels
        [[nodiscard]] auto height() const noexcept -> int { return height_; }

        // Read the color at the specified pixel coordinates
        // Throws if coordinates are out of bounds
        [[nodiscard]] auto pixel_at(int x_value, int y_value) const -> Color {
            bounds_check(x_value, y_value);
            return pixels_[to_index(x_value, y_value)];
        }

        // Write a color to the specified pixel coordinates
        // Throws if coordinates are out of bounds
        auto write_pixel(int x_value, int y_value, const Color &color) -> void {
            bounds_check(x_value, y_value);
            pixels_[to_index(x_value, y_value)] = color;
        }

    private:
        int width_;              // Canvas width in pixels
        int height_;             // Canvas height in pixels
        std::vector<Color> pixels_; // Pixel data stored in row-major order

        // Convert (x, y) coordinates to a linear index in the pixel array
        // Uses row-major ordering: index = y * width + x
        [[nodiscard]] auto to_index(int x_value, int y_value) const noexcept -> std::size_t {
            return static_cast<std::size_t>((y_value * width_) + x_value);
        }

        // Validate that pixel coordinates are within canvas bounds
        // Throws std::out_of_range if coordinates are invalid
        auto bounds_check(int x_value, int y_value) const -> void {
            if (x_value < 0 || x_value >= width_ || y_value < 0 || y_value >= height_) {
                throw std::out_of_range("Pixel coordinates out of canvas bounds.");
            }
        }
    };

    // Convert a canvas to PPM (Portable Pixel Map) format string
    // PPM is a simple image format that stores pixel data as plain text
    // - P3 header indicates ASCII PPM format
    // - Width and height dimensions
    // - 255 indicates maximum color value
    // - Pixel data in RGB triplets, with lines limited to 70 characters
    inline auto canvas_to_ppm(const Canvas &c) -> std::string {
        std::ostringstream oss;
        // PPM header
        oss << "P3\n"
                << c.width() << " " << c.height() << "\n"
                << "255\n";

        // Scale color from [0.0, 1.0] to [0, 255]
        auto scale_color = [](double value) -> int {
            // Clamp color values to [0.0, 1.0] to handle out-of-gamut colors
            value = std::clamp(value, 0.0, 1.0);
            // Scale to [0, 255] and round to nearest integer
            return static_cast<int>(std::round(value * 255));
        };

        // Track line length to ensure no line exceeds 70 characters (PPM spec)
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

                // Write each RGB component with proper line wrapping
                for (const auto &str : {r_str, g_str, b_str}) {
                    if (line_length > 0) {
                        // Check if adding this value would exceed 70 characters
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
            // End each row with a newline
            oss << "\n";
            line_length = 0;
        }
        return oss.str();
    }
} // namespace rtc
