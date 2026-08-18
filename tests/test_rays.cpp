#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <cmath>

#include "lib/matrix.hpp"
#include "lib/tuple.hpp"
#include "lib/rays.hpp"
#include "lib/transform.hpp"

using namespace rtc;
using Catch::Approx;

SCENARIO("Creating and querying a ray", "[ray]") {
    GIVEN("origin <- point(1, 2, 3) and direction <- vector(4, 5, 6)") {
        Tuple origin = Tuple::point(1.0, 2.0, 3.0);
        Tuple direction = Tuple::vector(4.0, 5.0, 6.0);

        WHEN("r <- ray(origin, direction)") {
            Ray r{origin, direction};

            THEN("r.origin == origin") {
                CHECK(r.origin == origin);
            }
            AND_THEN("r.direction == direction") {
                CHECK(r.direction == direction);
            }
        }
    }
}

SCENARIO("Computing a point from a distance", "[ray]") {
    GIVEN("r <- ray(point(2, 3, 4), vector(1, 0, 0))") {
        Ray r{Tuple::point(2.0, 3.0, 4.0), Tuple::vector(1.0, 0.0, 0.0)};

        THEN("position(r, 0) == point(2, 3, 4)") {
            CHECK(position(r, 0.0) == Tuple::point(2.0, 3.0, 4.0));
        }
        AND_THEN("position(r, 1) == point(3, 3, 4)") {
            CHECK(position(r, 1.0) == Tuple::point(3.0, 3.0, 4.0));
        }
        AND_THEN("position(r, -1) == point(1, 3, 4)") {
            CHECK(position(r, -1.0) == Tuple::point(1.0, 3.0, 4.0));
        }
        AND_THEN("position(r, 2.5) == point(4.5, 3, 4)") {
            CHECK(position(r, 2.5) == Tuple::point(4.5, 3.0, 4.0));
        }
    }
}

SCENARIO("Translating a ray", "[ray][transform]") {
    GIVEN("r <- ray(point(1, 2, 3), vector(0, 1, 0)) and m <- translation(3, 4, 5)") {
        Ray r{Tuple::point(1.0, 2.0, 3.0), Tuple::vector(0.0, 1.0, 0.0)};
        Matrix m = Transform::translation(3.0, 4.0, 5.0);

        WHEN("r2 <- transform(r, m)") {
            Ray r2 = transform(r, m);

            THEN("r2.origin == point(4, 6, 8)") {
                CHECK(r2.origin == Tuple::point(4.0, 6.0, 8.0));
            }
            AND_THEN("r2.direction == vector(0, 1, 0)") {
                CHECK(r2.direction == Tuple::vector(0.0, 1.0, 0.0));
            }
        }
    }
}

SCENARIO("Scaling a ray", "[ray][transform]") {
    GIVEN("r <- ray(point(1, 2, 3), vector(0, 1, 0)) and m <- scaling(2, 3, 4)") {
        Ray r{Tuple::point(1.0, 2.0, 3.0), Tuple::vector(0.0, 1.0, 0.0)};
        Matrix m = Transform::scaling(2.0, 3.0, 4.0);

        WHEN("r2 <- transform(r, m)") {
            Ray r2 = transform(r, m);

            THEN("r2.origin == point(2, 6, 12)") {
                CHECK(r2.origin == Tuple::point(2.0, 6.0, 12.0));
            }
            AND_THEN("r2.direction == vector(0, 3, 0)") {
                CHECK(r2.direction == Tuple::vector(0.0, 3.0, 0.0));
            }
        }
    }
}
