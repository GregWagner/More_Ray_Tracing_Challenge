#pragma once

#include <cmath>

#include "lib/matrix.hpp"

using namespace rtc;

class Transform {
public:
    static Matrix translation(double x, double y, double z) {
        Matrix m = identity_matrix(4);
        m(0, 3) = x;
        m(1, 3) = y;
        m(2, 3) = z;
        return m;
    }

    static Matrix scaling(double x, double y, double z) {
        Matrix m = identity_matrix(4);
        m(0, 0) = x;
        m(1, 1) = y;
        m(2, 2) = z;
        return m;
    }

    static Matrix rotation_x(double rad) {
        Matrix m = identity_matrix(4);
        m(1, 1) = std::cos(rad);
        m(1, 2) = -std::sin(rad);
        m(2, 1) = std::sin(rad);
        m(2, 2) = std::cos(rad);
        return m;
    }

    static Matrix rotation_y(double rad) {
        Matrix m = identity_matrix(4);
        m(0, 0) = std::cos(rad);
        m(0, 2) = std::sin(rad);
        m(2, 0) = -std::sin(rad);
        m(2, 2) = std::cos(rad);
        return m;
    }

    static Matrix rotation_z(double rad) {
        Matrix m = identity_matrix(4);
        m(0, 0) = std::cos(rad);
        m(0, 1) = -std::sin(rad);
        m(1, 0) = std::sin(rad);
        m(1, 1) = std::cos(rad);
        return m;
    }

    static Matrix shearing(double xy, double xz, double yx, double yz, double zx, double zy) {
        Matrix m = identity_matrix(4);
        m(0, 1) = xy;
        m(0, 2) = xz;
        m(1, 0) = yx;
        m(1, 2) = yz;
        m(2, 0) = zx;
        m(2, 1) = zy;
        return m;
    }


    static Matrix orientation(const Tuple &left, const Tuple &true_up, const Tuple &forward) {
        Matrix m = identity_matrix(4);
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
    static Matrix orientation(const Tuple &forward_dir, const Tuple &up_dir) {
        Tuple forward = normalize(forward_dir);
        Tuple left = cross(forward, normalize(up_dir));
        Tuple true_up = cross(left, forward);
        return orientation(left, true_up, forward);
    }

    // Refactored view_transform utilizing orientation()
    static Matrix view_transform(const Tuple &from, const Tuple &to, const Tuple &up) {
        Tuple forward = normalize(to - from);
        Tuple left = cross(forward, normalize(up));
        Tuple true_up = cross(left, forward);

        return orientation(left, true_up, forward) * translation(-from.x_value, -from.y_value, -from.z_value);
    }
};

// Free-function wrappers
inline Matrix orientation(const Tuple &left, const Tuple &true_up, const Tuple &forward) {
    return Transform::orientation(left, true_up, forward);
}

inline Matrix orientation(const Tuple &forward_dir, const Tuple &up_dir) {
    return Transform::orientation(forward_dir, up_dir);
}

// ============================================================================
// Free-function wrappers (if tests call translation(...) directly)
// ============================================================================

inline Matrix translation(double x, double y, double z) {
    return Transform::translation(x, y, z);
}

inline Matrix scaling(double x, double y, double z) {
    return Transform::scaling(x, y, z);
}

inline Matrix rotation_x(double rad) {
    return Transform::rotation_x(rad);
}

inline Matrix rotation_y(double rad) {
    return Transform::rotation_y(rad);
}

inline Matrix rotation_z(double rad) {
    return Transform::rotation_z(rad);
}

inline Matrix shearing(double xy, double xz, double yx, double yz, double zx, double zy) {
    return Transform::shearing(xy, xz, yx, yz, zx, zy);
}

inline Matrix view_transform(const Tuple &from, const Tuple &to, const Tuple &up) {
    return Transform::view_transform(from, to, up);
}
