#include "rays.hpp"

namespace rtc {
    // Free function wrapper for calculating position along a ray
    auto position(const Ray &r, double distance) -> Tuple {
        return r.position(distance);
    }

    // Free function wrapper for transforming a ray
    auto transform(const Ray &r, const Matrix &m) -> Ray {
        return r.transform(m);
    }
} // namespace rtc
