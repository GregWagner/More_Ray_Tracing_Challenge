#include "PixelMath.hpp"
#include "raylib.h"
#include <string_view>

namespace {
// Window configuration constants
constexpr int screenWidth{800};      // Window width in pixels
constexpr int screenHeight{450};     // Window height in pixels
constexpr int targetFps{60};        // Target frames per second
constexpr std::string_view windowTitle{"Raylib - Draw Pixel"};

// Calculate the center pixel of the window at compile time
constexpr auto centerPixel = PixelApp::calculateCenter(screenWidth, screenHeight);

// RAII wrapper for Raylib window initialization and cleanup
// Ensures the window is properly closed when the object goes out of scope
class WindowManager {
public:
    // Initialize the Raylib window with specified dimensions, title, and target FPS
    WindowManager(int width, int height, std::string_view title, int fps) {
        InitWindow(width, height, title.data());
        SetTargetFPS(fps);
    }

    // Automatically close the window when the WindowManager is destroyed
    ~WindowManager() noexcept {
        CloseWindow();
    }

    // Prevent copying and moving to ensure single window instance
    WindowManager(const WindowManager &) = delete;
    WindowManager &operator=(const WindowManager &) = delete;
    WindowManager(WindowManager &&) = delete;
    WindowManager &operator=(WindowManager &&) = delete;

    // Check if the window should close (user clicked X or pressed ESC)
    [[nodiscard]] static auto shouldClose() noexcept -> bool {
        return WindowShouldClose();
    }
};

// RAII wrapper for Raylib drawing frame
// Ensures EndDrawing() is called even if an exception occurs during the frame
class ScopedFrame {
public:
    // Begin a new drawing frame
    ScopedFrame() noexcept {
        BeginDrawing();
    }

    // End the drawing frame and present to screen
    ~ScopedFrame() noexcept {
        EndDrawing();
    }

    // Prevent copying and moving to ensure proper RAII semantics
    ScopedFrame(const ScopedFrame &) = delete;
    ScopedFrame &operator=(const ScopedFrame &) = delete;
    ScopedFrame(ScopedFrame &&) = delete;
    ScopedFrame &operator=(ScopedFrame &&) = delete;
};
} // namespace

// Main entry point for the Raylib pixel drawing application
auto main() -> int {
    // Initialize the window with RAII wrapper (auto-cleanup on exit)
    const WindowManager window{screenWidth, screenHeight, windowTitle, targetFps};

    // Compile-time assertion to ensure center pixel is within bounds
    static_assert(PixelApp::isWithinBounds(centerPixel, screenWidth, screenHeight),
                  "Center pixel coordinate must remain inside window bounds");

    // Main game loop: continues until window should close
    while (!WindowManager::shouldClose()) {
        // Begin a new drawing frame (auto-ends when scope exits)
        const ScopedFrame frame{};
        
       // Clear the screen with black background
        ClearBackground(BLACK);

        // Draw a single red pixel at the center of the screen
        DrawPixel(centerPixel.x, centerPixel.y, RED);
    }
}
