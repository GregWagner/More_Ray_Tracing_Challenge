#include "PixelMath.hpp"
#include "raylib.h"
#include <string_view>

namespace {
constexpr int screenWidth{800};
constexpr int screenHeight{450};
constexpr int targetFps{60};
constexpr std::string_view windowTitle{"Raylib - Draw Pixel"};

constexpr auto centerPixel = PixelApp::calculateCenter(screenWidth, screenHeight);

class WindowManager {
public:
    WindowManager(int width, int height, std::string_view title, int fps) {
        InitWindow(width, height, title.data());
        SetTargetFPS(fps);
    }

    ~WindowManager() noexcept {
        CloseWindow();
    }

    WindowManager(const WindowManager &) = delete;
    WindowManager &operator=(const WindowManager &) = delete;
    WindowManager(WindowManager &&) = delete;
    WindowManager &operator=(WindowManager &&) = delete;

    [[nodiscard]] static bool shouldClose() noexcept {
        return WindowShouldClose();
    }
};

class ScopedFrame {
public:
    ScopedFrame() noexcept {
        BeginDrawing();
    }

    ~ScopedFrame() noexcept {
        EndDrawing();
    }

    ScopedFrame(const ScopedFrame &) = delete;
    ScopedFrame &operator=(const ScopedFrame &) = delete;
    ScopedFrame(ScopedFrame &&) = delete;
    ScopedFrame &operator=(ScopedFrame &&) = delete;
};
} // namespace

int main() {
    const WindowManager window{screenWidth, screenHeight, windowTitle, targetFps};

    static_assert(PixelApp::isWithinBounds(centerPixel, screenWidth, screenHeight),
                  "Center pixel coordinate must remain inside window bounds");

    while (!WindowManager::shouldClose()) {
        const ScopedFrame frame{};
        ClearBackground(BLACK);

        DrawPixel(centerPixel.x, centerPixel.y, RED);
    }
}
