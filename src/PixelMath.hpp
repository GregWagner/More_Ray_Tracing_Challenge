#pragma once

namespace PixelApp {
// Point represents a 2D coordinate in pixel space
// Used for positioning elements within a window or canvas
struct Point
{
    int x{0}; // X coordinate (horizontal position)
    int y{0}; // Y coordinate (vertical position)
};

// Calculate the center point of a rectangular area
// Returns the pixel coordinates at the center of the specified width and height
// This is a constexpr function that can be evaluated at compile time
[[nodiscard]] constexpr auto calculateCenter(int width, int height) noexcept -> Point {
    return {width / 2, height / 2};
}

// Check if a point is within the bounds of a rectangular area
// Returns true if the point's coordinates are valid (non-negative and less than dimensions)
// Useful for validating that pixel operations won't go out of bounds
[[nodiscard]] constexpr auto isWithinBounds(Point pt, int width, int height) noexcept -> bool {
    return pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height;
}
} // namespace PixelApp
