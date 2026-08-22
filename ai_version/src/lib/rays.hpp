#pragma once

#include "matrix.hpp"
#include "tuple.hpp"

namespace rtc {
    // Ray represents a ray in 3D space with an origin point and direction vector.
    // Used for ray tracing to determine intersections with objects in the scene.
    struct Ray {
        Tuple origin;    // Starting point of the ray (point, w=1)
        Tuple direction; // Direction the ray travels (vector, w=0)

        // Calculate the point along the ray at a given distance
        // Formula: origin + direction * distance
        auto position(double distance) const -> Tuple {
            return origin + direction * distance;
        }

        // Apply a transformation matrix to the ray
        // Transforms both origin and direction by the matrix
        auto transform(const Matrix &m) const -> Ray {
            return Ray{m * origin, m * direction};
        }
    };

    // Free function wrapper for calculating position along a ray
    auto position(const Ray &r, double distance) -> Tuple;

    // Free function wrapper for transforming a ray
    auto transform(const Ray &r, const Matrix &m) -> Ray;
}
