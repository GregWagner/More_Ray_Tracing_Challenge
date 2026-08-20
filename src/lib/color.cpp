#include "color.hpp"

#include <ostream>

namespace rtc {
    // Stream output operator for debugging and logging
    // Outputs color in format: Color(red, green, blue)
    auto operator<<(std::ostream &os, const Color &color) -> std::ostream & {
        os << "Color(" << color.red << ", " << color.green << ", " << color.blue << ")";
        return os;
    }
} // namespace rtc
