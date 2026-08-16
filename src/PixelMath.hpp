#pragma once

namespace PixelApp {
struct Point
{
    int x{0};
    int y{0};
};

// Computes center coordinates without side effects
[[nodiscard]] constexpr Point calculateCenter(int width, int height) noexcept {
    return {width / 2, height / 2};
}

// Validates point bounds inside screen dimensions
[[nodiscard]] constexpr bool isWithinBounds(Point pt, int width, int height) noexcept {
    return pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height;
}
} // namespace PixelApp
