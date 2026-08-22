#pragma once

#include <cmath>

#include "lib/matrix.hpp"

// Transform provides static methods for creating transformation matrices.
// These matrices are used to translate, scale, rotate, and shear objects in 3D space.
// All transformations return 4x4 matrices compatible with the Tuple representation.
class Transform {
public:
    // Create a translation matrix that moves objects by (x, y, z)
    // Translation affects points but not vectors
    static auto translation(double x, double y, double z) -> rtc::Matrix;

    // Create a scaling matrix that scales objects by (x, y, z)
    // Scaling affects both points and vectors
    static auto scaling(double x, double y, double z) -> rtc::Matrix;

    // Create a rotation matrix around the X-axis
    // Angle is specified in radians
    static auto rotation_x(double rad) -> rtc::Matrix;

    // Create a rotation matrix around the Y-axis
    // Angle is specified in radians
    static auto rotation_y(double rad) -> rtc::Matrix;

    // Create a rotation matrix around the Z-axis
    // Angle is specified in radians
    static auto rotation_z(double rad) -> rtc::Matrix;

    // Create a shearing matrix for skewing transformations
    // Parameters control how each axis moves in proportion to others
    static auto shearing(double xy, double xz, double yx, double yz, double zx, double zy) -> rtc::Matrix;

    // Create an orientation matrix from pre-computed basis vectors
    // left, true_up, and forward form an orthonormal basis
    static auto orientation(const rtc::Tuple &left, const rtc::Tuple &true_up, const rtc::Tuple &forward) -> rtc::Matrix;

    // Overload: computes orientation directly from look direction and up vector
    // Automatically computes the orthonormal basis from the given directions
    static auto orientation(const rtc::Tuple &forward_dir, const rtc::Tuple &up_dir) -> rtc::Matrix;

    // Create a view transformation matrix for camera positioning
    // Transforms world coordinates to camera coordinates
    // from: camera position, to: point to look at, up: up direction
    static auto view_transform(const rtc::Tuple &from, const rtc::Tuple &to, const rtc::Tuple &up) -> rtc::Matrix;
};

// Free-function wrappers for convenience (allow calling without Transform:: prefix)

// Orientation wrappers
auto orientation(const rtc::Tuple &left, const rtc::Tuple &true_up, const rtc::Tuple &forward) -> rtc::Matrix;
auto orientation(const rtc::Tuple &forward_dir, const rtc::Tuple &up_dir) -> rtc::Matrix;

// Transformation wrappers
auto translation(double x, double y, double z) -> rtc::Matrix;
auto scaling(double x, double y, double z) -> rtc::Matrix;
auto rotation_x(double rad) -> rtc::Matrix;
auto rotation_y(double rad) -> rtc::Matrix;
auto rotation_z(double rad) -> rtc::Matrix;
auto shearing(double xy, double xz, double yx, double yz, double zx, double zy) -> rtc::Matrix;
auto view_transform(const rtc::Tuple &from, const rtc::Tuple &to, const rtc::Tuple &up) -> rtc::Matrix;
