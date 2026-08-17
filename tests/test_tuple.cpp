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
    GIVEN("a <- tuple(4.3, -4.2, 3.1, 0.0)") {
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

SCENARIO("point() creates tuples with w=1", "[tuple][bdd]") {
    GIVEN("p <- point(4, -4, 3)") {
        auto p = Tuple::point(4, -4, 3);
        THEN("p = tuple(4, -4, 3, 1)") {
            CHECK(p == Tuple(4, -4, 3, 1));
        }
    }
}

SCENARIO("vector() creates tuples with w=0", "[tuple][bdd]") {
    GIVEN("v <- vector(4, -4, 3)") {
        auto v = Tuple::vector(4, -4, 3);
        THEN("v = tuple(4, -4, 3, 0)") {
            CHECK(v == Tuple(4, -4, 3, 0));
        }
    }
}

SCENARIO("Adding two tuples", "[tuple][bdd]") {
    GIVEN("a1 ← tuple(3, -2, 5, 1)") {
        Tuple a1(3, -2, 5, 1);
        AND_GIVEN("a2 ← tuple(-2, 3, 1, 0)") {
            Tuple a2(-2, 3, 1, 0);
            THEN("a1 + a2 = tuple(1, 1, 6, 1)") {
                auto result = a1 + a2;
                CHECK(result == Tuple(1, 1, 6, 1));
            }
        }
    }
}

SCENARIO("Subtracting two points", "[tuple][bdd]") {
    GIVEN("p1 <- point(3, 2, 1)") {
        auto p1 = Tuple::point(3, 2, 1);
        AND_GIVEN("p2 ← point(5, 6, 7)") {
            auto p2 = Tuple::point(5, 6, 7);
            THEN("p1 - p2 = vector(-2, -4, -6)") {
                auto result = p1 - p2;
                CHECK(result == Tuple::vector(-2, -4, -6));
            }
        }
    }
}

SCENARIO("Subtracting a vector from a point", "[tuple][bdd]") {
    GIVEN("p <- point(3, 2, 1)") {
        auto p = Tuple::point(3, 2, 1);
        AND_GIVEN("v ← vector(5, 6, 7)") {
            auto v = Tuple::vector(5, 6, 7);
            THEN("p - v = point(-2, -4, -6)") {
                auto result = p - v;
                CHECK(result == Tuple::point(-2, -4, -6));
            }
        }
    }
}

SCENARIO("Subtracting two vectors", "[tuple][bdd]") {
    GIVEN("v1 <- vector(3, 2, 1)") {
        auto v1 = Tuple::vector(3, 2, 1);
        AND_GIVEN("v2 ← vector(5, 6, 7)") {
            auto v2 = Tuple::vector(5, 6, 7);
            THEN("v1 - v2 = vector(-2, -4, -6)") {
                auto result = v1 - v2;
                CHECK(result == Tuple::vector(-2, -4, -6));
            }
        }
    }
}

SCENARIO("Subtracting a vector from the zero vector", "[tuple][bdd]") {
    GIVEN("zero <- vector(0, 0, 0)") {
        auto zero = Tuple::vector(0, 0, 0);
        AND_GIVEN("v ← vector(1, -2, 3)") {
            auto v = Tuple::vector(1, -2, 3);
            THEN("zero - v = vector(-1, 2, -3)") {
                auto result = zero - v;
                CHECK(result == Tuple::vector(-1, 2, -3));
            }
        }
    }
}

SCENARIO("Negating a tuple", "[tuple][bdd]") {
    GIVEN("a <- tuple(1, -2, 3, -4)") {
        Tuple a(1, -2, 3, -4);
        THEN("-a = tuple(-1, 2, -3, 4)") {
            CHECK(-a == Tuple(-1, 2, -3, 4));
        }
    }
}

SCENARIO("Multiplying a tuple by a scalar", "[tuple][bdd]") {
    GIVEN("a <- tuple(1, -2, 3, -4)") {
        Tuple a(1, -2, 3, -4);
        THEN("a * 3.5 = tuple(3.5, -7, 10.5, -14)") {
            CHECK(a * 3.5 == Tuple(3.5, -7, 10.5, -14));
        }
    }
}

SCENARIO("Multiplying a tuple by a fraction", "[tuple][bdd]") {
    GIVEN("a <- tuple(1, -2, 3, -4)") {
        Tuple a(1, -2, 3, -4);
        THEN("a * 0.5 = tuple(0.5, -1, 1.5, -2)") {
            CHECK(a * 0.5 == Tuple(0.5, -1, 1.5, -2));
        }
    }
}

SCENARIO("Dividing a tuple by a scalar", "[tuple][bdd]") {
    GIVEN("a <- tuple(1, -2, 3, -4)") {
        Tuple a(1, -2, 3, -4);
        THEN("a / 2 = tuple(0.5, -1, 1.5, -2)") {
            CHECK(a / 2 == Tuple(0.5, -1, 1.5, -2));
        }
    }
}

SCENARIO("Computing the magnitude of unit vectors", "[tuple][bdd]") {
    GIVEN("unit vectors along each axis") {
        auto v1 = Tuple::vector(1, 0, 0);
        auto v2 = Tuple::vector(0, 1, 0);
        auto v3 = Tuple::vector(0, 0, 1);
        THEN("each has magnitude 1") {
            CHECK(magnitude(v1) == 1);
            CHECK(magnitude(v2) == 1);
            CHECK(magnitude(v3) == 1);
        }
    }
}

SCENARIO("Computing the magnitude of vector(1, 2, 3)", "[tuple][bdd]") {
    GIVEN("v <- vector(1, 2, 3)") {
        auto v = Tuple::vector(1, 2, 3);
        THEN("magnitude(v) = sqrt(14)") {
            CHECK(magnitude(v) == Approx(std::sqrt(14)));
        }
    }
}

SCENARIO("Computing the magnitude of vector(-1, -2, -3)", "[tuple][bdd]") {
    GIVEN("v <- vector(-1, -2, -3)") {
        auto v = Tuple::vector(-1, -2, -3);
        THEN("magnitude(v) = sqrt(14)") {
            CHECK(magnitude(v) == Approx(std::sqrt(14)));
        }
    }
}

SCENARIO("Normalizing vector(4, 0, 0) gives (1, 0, 0)", "[tuple][bdd]") {
    GIVEN("v <- vector(4, 0, 0)") {
        auto v = Tuple::vector(4, 0, 0);
        THEN("normalize(v) = vector(1, 0, 0)") {
            CHECK(normalize(v) == Tuple::vector(1, 0, 0));
        }
    }
}

SCENARIO("Normalizing vector(1, 2, 3)", "[tuple][bdd]") {
    GIVEN("v <- vector(1, 2, 3)") {
        auto v = Tuple::vector(1, 2, 3);
        THEN("normalize(v) = vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)") {
            auto result = normalize(v);
            CHECK(result.x_value == Approx(1 / std::sqrt(14)));
            CHECK(result.y_value == Approx(2 / std::sqrt(14)));
            CHECK(result.z_value == Approx(3 / std::sqrt(14)));
            CHECK(result.is_vector());
        }
    }
}

SCENARIO("The magnitude of a normalized vector", "[tuple][bdd]") {
    GIVEN("v <- vector(1, 2, 3)") {
        auto v = Tuple::vector(1, 2, 3);
        THEN("magnitude(normalize(v)) = 1") {
            CHECK(magnitude(normalize(v)) == Approx(1));
        }
    }
}

SCENARIO("The dot product of two tuples", "[tuple][bdd]") {
    GIVEN("a <- vector(1, 2, 3)") {
        auto a = Tuple::vector(1, 2, 3);
        AND_GIVEN("b <- vector(2, 3, 4)") {
            auto b = Tuple::vector(2, 3, 4);
            THEN("dot(a, b) = 20") {
                CHECK(dot(a, b) == 20);
            }
        }
    }
}

SCENARIO("The cross product of two vectors", "[tuple][bdd]") {
    GIVEN("a <- vector(1, 2, 3)") {
        auto a = Tuple::vector(1, 2, 3);
        AND_GIVEN("b <- vector(2, 3, 4)") {
            auto b = Tuple::vector(2, 3, 4);
            THEN("cross(a, b) = vector(-1, 2, -1)") {
                CHECK(cross(a, b) == Tuple::vector(-1, 2, -1));
            }
            THEN("cross(b, a) = vector(1, -2, 1)") {
                CHECK(cross(b, a) == Tuple::vector(1, -2, 1));
            }
        }
    }
}
