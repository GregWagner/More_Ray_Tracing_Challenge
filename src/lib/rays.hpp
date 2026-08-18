#pragma once


#include "matrix.hpp"
#include "tuple.hpp"

namespace rtc {
    struct Ray {
        Tuple origin;
        Tuple direction;

        Tuple position(double distance) const {
            return origin + direction * distance;
        }

        Ray transform(const Matrix &m) const {
            return Ray{m * origin, m * direction};
        }
    };

    inline Tuple position(const Ray &r, double distance) {
        return r.position(distance);
    }

    inline Ray transform(const Ray &r, const Matrix &m) {
        return r.transform(m);
    }
}
