#pragma once

#include <cmath>

#include "lib/matrix.hpp"

class Transform {
public:
    static auto translation(double x, double y, double z) -> rtc::Matrix {
        rtc::Matrix m = rtc::identity_matrix(4);
        m(0, 3) = x;
        m(1, 3) = y;
        m(2, 3) = z;
        return m;
    }

    static auto scaling(double x, double y, double z) -> rtc::Matrix {
        rtc::Matrix m = rtc::identity_matrix(4);
        m(0, 0) = x;
        m(1, 1) = y;
        m(2, 2) = z;
        return m;
    }

    static auto rotation_x(double rad) -> rtc::Matrix {
        rtc::Matrix m = rtc::identity_matrix(4);
        m(1, 1) = std::cos(rad);
        m(1, 2) = -std::sin(rad);
        m(2, 1) = std::sin(rad);
        m(2, 2) = std::cos(rad);
        return m;
    }

    static auto rotation_y(double rad) -> rtc::Matrix {
        rtc::Matrix m = rtc::identity_matrix(4);
        m(0, 0) = std::cos(rad);
        m(0, 2) = std::sin(rad);
        m(2, 0) = -std::sin(rad);
        m(2, 2) = std::cos(rad);
        return m;
    }

    static auto rotation_z(double rad) -> rtc::Matrix {
        rtc::Matrix m = rtc::identity_matrix(4);
        m(0, 0) = std::cos(rad);
        m(0, 1) = -std::sin(rad);
        m(1, 0) = std::sin(rad);
        m(1, 1) = std::cos(rad);
        return m;
    }

    static auto shearing(double xy, double xz, double yx, double yz, double zx, double zy) -> rtc::Matrix {
        rtc::Matrix m = rtc::identity_matrix(4);
        m(0, 1) = xy;
        m(0, 2) = xz;
        m(1, 0) = yx;
        m(1, 2) = yz;
        m(2, 0) = zx;
        m(2, 1) = zy;
        return m;
    }


    static auto orientation(const rtc::Tuple &left, const rtc::Tuple &true_up, const rtc::Tuple &forward) -> rtc::Matrix {
        rtc::Matrix m = rtc::identity_matrix(4);
        m(0, 0) = left.x_value;
        m(0, 1) = left.y_value;
        m(0, 2) = left.z_value;
        m(1, 0) = true_up.x_value;
        m(1, 1) = true_up.y_value;
        m(1, 2) = true_up.z_value;
        m(2, 0) = -forward.x_value;
        m(2, 1) = -forward.y_value;
        m(2, 2) = -forward.z_value;
        return m;
    }

    // Overload: computes orientation directly from look direction and up vector
    static auto orientation(const rtc::Tuple &forward_dir, const rtc::Tuple &up_dir) -> rtc::Matrix {
        rtc::Tuple forward = rtc::normalize(forward_dir);
        rtc::Tuple left = rtc::cross(forward, rtc::normalize(up_dir));
        rtc::Tuple true_up = rtc::cross(left, forward);
        return orientation(left, true_up, forward);
    }

    // Refactored view_transform utilizing orientation()
    static auto view_transform(const rtc::Tuple &from, const rtc::Tuple &to, const rtc::Tuple &up) -> rtc::Matrix {
        rtc::Tuple forward = rtc::normalize(to - from);
        rtc::Tuple left = rtc::cross(forward, rtc::normalize(up));
        rtc::Tuple true_up = rtc::cross(left, forward);

        return orientation(left, true_up, forward) * translation(-from.x_value, -from.y_value, -from.z_value);
    }
};

// Free-function wrappers
inline auto orientation(const rtc::Tuple &left, const rtc::Tuple &true_up, const rtc::Tuple &forward) -> rtc::Matrix {
    return Transform::orientation(left, true_up, forward);
}

inline auto orientation(const rtc::Tuple &forward_dir, const rtc::Tuple &up_dir) -> rtc::Matrix {
    return Transform::orientation(forward_dir, up_dir);
}

// ============================================================================
// Free-function wrappers (if tests call translation(...) directly)
// ============================================================================

inline auto translation(double x, double y, double z) -> rtc::Matrix {
    return Transform::translation(x, y, z);
}

inline auto scaling(double x, double y, double z) -> rtc::Matrix {
    return Transform::scaling(x, y, z);
}

inline auto rotation_x(double rad) -> rtc::Matrix {
    return Transform::rotation_x(rad);
}

inline auto rotation_y(double rad) -> rtc::Matrix {
    return Transform::rotation_y(rad);
}

inline auto rotation_z(double rad) -> rtc::Matrix {
    return Transform::rotation_z(rad);
}

inline auto shearing(double xy, double xz, double yx, double yz, double zx, double zy) -> rtc::Matrix {
    return Transform::shearing(xy, xz, yx, yz, zx, zy);
}

inline auto view_transform(const rtc::Tuple &from, const rtc::Tuple &to, const rtc::Tuple &up) -> rtc::Matrix {
    return Transform::view_transform(from, to, up);
}
