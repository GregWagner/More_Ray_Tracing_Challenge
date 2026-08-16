#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "lib/tuple.hpp"

using namespace rtc;
using Catch::Approx;

SCENARIO("A tuple with w = 1.0 is a point", "[tuple][bdd]") {
    GIVEN("a <- tuple(4.3, -4.2, 3.1, 1.0)") {
        Tuple a(4.3, -4.2, 3.1, 1.0);

        THEN("the coordinates match the input values") {
            CHECK(a.x_value == Approx(4.3));
            CHECK(a.y_value == Approx(-4.2));
            CHECK(a.z_value == Approx(3.1));
            CHECK(a.w_value == Approx(1.0));
        }
        THEN("it is classified as a point") {
            CHECK(a.is_point());
            CHECK_FALSE(a.is_vector());
        }
    }
}


SCENARIO("A tuple with w = 0 is a vector", "[tuple][bdd]") {
    GIVEN("a <- typle(4.3, -4.2, 3.1, 1.0)") {
        Tuple a(4.3, -4.2, 3.1, 0.0);

        THEN("the coordinates match the input values") {
            CHECK(a.x_value == Approx(4.3));
            CHECK(a.y_value == Approx(-4.2));
            CHECK(a.z_value == Approx(3.1));
            CHECK(a.w_value == Approx(0.0));
        }
        THEN("it is classified as a vector") {
            CHECK_FALSE(a.is_point());
            CHECK(a.is_vector());
        }
    }
}

SCENARIO("Magnitude and normalization", "[tuple][bdd]") {
    GIVEN("a vector (1,2,3)") {
        Tuple v = Tuple::vector(1, 2, 3);

        WHEN("magnitude is computed") {
            THEN("it equals sqrt(14)") {
                REQUIRE(magnitude(v) == Approx(std::sqrt(14.0)));
            }
        }

        WHEN("the vector is normalized") {
            Tuple n = normalize(v);
            THEN("the result is the normalized vector") {
                REQUIRE(n == Tuple(1 / std::sqrt(14.0), 2 / std::sqrt(14.0), 3 / std::sqrt(14.0), 0.0));
            }
        }
    }
}
