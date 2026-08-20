#pragma once


#include "matrix.hpp"
#include "tuple.hpp"

namespace rtc {
    struct Ray {
        Tuple origin;
        Tuple direction;

        auto position(double distance) const -> Tuple {
            return origin + direction * distance;
        }

        auto transform(const Matrix &m) const -> Ray {
            return Ray{m * origin, m * direction};
        }
    };

    inline auto position(const Ray &r, double distance) -> Tuple {
        return r.position(distance);
    }

    inline auto transform(const Ray &r, const Matrix &m) -> Ray {
        return r.transform(m);
    }
}
