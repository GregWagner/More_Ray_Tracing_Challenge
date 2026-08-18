#include <catch2/catch_test_macros.hpp>
#include <cmath>

#include "lib/tuple.hpp"
#include "lib/matrix.hpp"
#include "lib/transform.hpp"

using namespace rtc;

constexpr double pi = 3.14159265358979323846;
const double sqrt2_2 = std::sqrt(2.0) / 2.0;

SCENARIO("Multiplying by a translation matrix", "[matrix][transform][bdd]") {
    GIVEN("transform <- translation(5, -3, 2)") {
        Matrix transform = Transform::translation(5.0, -3.0, 2.0);
        Tuple p = Tuple::point(-3.0, 4.0, 5.0);

        THEN("transform * p = point(2, 1, 7)") {
            CHECK(transform * p == Tuple::point(2.0, 1.0, 7.0));
        }
    }
}

SCENARIO("Multiplying by the inverse of a translation matrix", "[matrix][transform][bdd]") {
    GIVEN("transform <- translation(5, -3, 2)") {
        Matrix transform = Transform::translation(5.0, -3.0, 2.0);
        Matrix inv = inverse(transform);
        Tuple p = Tuple::point(-3.0, 4.0, 5.0);

        THEN("inv * p = point(-8, 7, 3)") {
            CHECK(inv * p == Tuple::point(-8.0, 7.0, 3.0));
        }
    }
}

SCENARIO("Translation does not affect vectors", "[matrix][transform][bdd]") {
    GIVEN("transform <- translation(5, -3, 2)") {
        Matrix transform = Transform::translation(5.0, -3.0, 2.0);
        Tuple v = Tuple::vector(-3.0, 4.0, 5.0);

        THEN("transform * v = v") {
            CHECK(transform * v == v);
        }
    }
}

SCENARIO("A scaling matrix applied to a point", "[matrix][transform][bdd]") {
    GIVEN("transform <- scaling(2, 3, 4)") {
        Matrix transform = Transform::scaling(2.0, 3.0, 4.0);
        Tuple p = Tuple::point(-4.0, 6.0, 8.0);

        THEN("transform * p = point(-8, 18, 32)") {
            CHECK(transform * p == Tuple::point(-8.0, 18.0, 32.0));
        }
    }
}

SCENARIO("A scaling matrix applied to a vector", "[matrix][transform][bdd]") {
    GIVEN("transform <- scaling(2, 3, 4)") {
        Matrix transform = Transform::scaling(2.0, 3.0, 4.0);
        Tuple v = Tuple::vector(-4.0, 6.0, 8.0);

        THEN("transform * v = vector(-8, 18, 32)") {
            CHECK(transform * v == Tuple::vector(-8.0, 18.0, 32.0));
        }
    }
}

SCENARIO("Multiplying by the inverse of a scaling matrix", "[matrix][transform][bdd]") {
    GIVEN("transform <- scaling(2, 3, 4)") {
        Matrix transform = Transform::scaling(2.0, 3.0, 4.0);
        Matrix inv = inverse(transform);
        Tuple v = Tuple::vector(-4.0, 6.0, 8.0);

        THEN("inv * v = vector(-2, 2, 2)") {
            CHECK(inv * v == Tuple::vector(-2.0, 2.0, 2.0));
        }
    }
}

SCENARIO("Reflection is scaling by a negative value", "[matrix][transform][bdd]") {
    GIVEN("transform <- scaling(-1, 1, 1)") {
        Matrix transform = Transform::scaling(-1.0, 1.0, 1.0);
        Tuple p = Tuple::point(2.0, 3.0, 4.0);

        THEN("transform * p = point(-2, 3, 4)") {
            CHECK(transform * p == Tuple::point(-2.0, 3.0, 4.0));
        }
    }
}

SCENARIO("Rotating a point around the x axis", "[matrix][transform][bdd]") {
    GIVEN("p <- point(0, 1, 0)") {
        Tuple p = Tuple::point(0.0, 1.0, 0.0);
        Matrix half_quarter = Transform::rotation_x(pi / 4.0);
        Matrix full_quarter = Transform::rotation_x(pi / 2.0);

        THEN("half_quarter * p = point(0, sqrt(2)/2, sqrt(2)/2)") {
            CHECK(half_quarter * p == Tuple::point(0.0, sqrt2_2, sqrt2_2));
        }
        THEN("full_quarter * p = point(0, 0, 1)") {
            CHECK(full_quarter * p == Tuple::point(0.0, 0.0, 1.0));
        }
    }
}

SCENARIO("The inverse of an x-rotation rotates in the opposite direction", "[matrix][transform][bdd]") {
    GIVEN("p <- point(0, 1, 0)") {
        Tuple p = Tuple::point(0.0, 1.0, 0.0);
        Matrix half_quarter = Transform::rotation_x(pi / 4.0);
        Matrix inv = inverse(half_quarter);

        THEN("inv * p = point(0, sqrt(2)/2, -sqrt(2)/2)") {
            CHECK(inv * p == Tuple::point(0.0, sqrt2_2, -sqrt2_2));
        }
    }
}

SCENARIO("Rotating a point around the y axis", "[matrix][transform][bdd]") {
    GIVEN("p <- point(0, 0, 1)") {
        Tuple p = Tuple::point(0.0, 0.0, 1.0);
        Matrix half_quarter = Transform::rotation_y(pi / 4.0);
        Matrix full_quarter = Transform::rotation_y(pi / 2.0);

        THEN("half_quarter * p = point(sqrt(2)/2, 0, sqrt(2)/2)") {
            CHECK(half_quarter * p == Tuple::point(sqrt2_2, 0.0, sqrt2_2));
        }
        THEN("full_quarter * p = point(1, 0, 0)") {
            CHECK(full_quarter * p == Tuple::point(1.0, 0.0, 0.0));
        }
    }
}

SCENARIO("Rotating a point around the z axis", "[matrix][transform][bdd]") {
    GIVEN("p <- point(0, 1, 0)") {
        Tuple p = Tuple::point(0.0, 1.0, 0.0);
        Matrix half_quarter = Transform::rotation_z(pi / 4.0);
        Matrix full_quarter = Transform::rotation_z(pi / 2.0);

        THEN("half_quarter * p = point(-sqrt(2)/2, sqrt(2)/2, 0)") {
            CHECK(half_quarter * p == Tuple::point(-sqrt2_2, sqrt2_2, 0.0));
        }
        THEN("full_quarter * p = point(-1, 0, 0)") {
            CHECK(full_quarter * p == Tuple::point(-1.0, 0.0, 0.0));
        }
    }
}

SCENARIO("A shearing transformation moves x in proportion to y", "[matrix][transform][bdd]") {
    GIVEN("transform <- shearing(1, 0, 0, 0, 0, 0)") {
        Matrix transform = Transform::shearing(1.0, 0.0, 0.0, 0.0, 0.0, 0.0);
        Tuple p = Tuple::point(2.0, 3.0, 4.0);

        THEN("transform * p = point(5, 3, 4)") {
            CHECK(transform * p == Tuple::point(5.0, 3.0, 4.0));
        }
    }
}

SCENARIO("A shearing transformation moves x in proportion to z", "[matrix][transform][bdd]") {
    GIVEN("transform <- shearing(0, 1, 0, 0, 0, 0)") {
        Matrix transform = Transform::shearing(0.0, 1.0, 0.0, 0.0, 0.0, 0.0);
        Tuple p = Tuple::point(2.0, 3.0, 4.0);

        THEN("transform * p = point(6, 3, 4)") {
            CHECK(transform * p == Tuple::point(6.0, 3.0, 4.0));
        }
    }
}

SCENARIO("A shearing transformation moves y in proportion to x", "[matrix][transform][bdd]") {
    GIVEN("transform <- shearing(0, 0, 1, 0, 0, 0)") {
        Matrix transform = Transform::shearing(0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
        Tuple p = Tuple::point(2.0, 3.0, 4.0);

        THEN("transform * p = point(2, 5, 4)") {
            CHECK(transform * p == Tuple::point(2.0, 5.0, 4.0));
        }
    }
}

SCENARIO("A shearing transformation moves y in proportion to z", "[matrix][transform][bdd]") {
    GIVEN("transform <- shearing(0, 0, 0, 1, 0, 0)") {
        Matrix transform = Transform::shearing(0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
        Tuple p = Tuple::point(2.0, 3.0, 4.0);

        THEN("transform * p = point(2, 7, 4)") {
            CHECK(transform * p == Tuple::point(2.0, 7.0, 4.0));
        }
    }
}

SCENARIO("A shearing transformation moves z in proportion to x", "[matrix][transform][bdd]") {
    GIVEN("transform <- shearing(0, 0, 0, 0, 1, 0)") {
        Matrix transform = Transform::shearing(0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        Tuple p = Tuple::point(2.0, 3.0, 4.0);

        THEN("transform * p = point(2, 3, 6)") {
            CHECK(transform * p == Tuple::point(2.0, 3.0, 6.0));
        }
    }
}

SCENARIO("A shearing transformation moves z in proportion to y", "[matrix][transform][bdd]") {
    GIVEN("transform <- shearing(0, 0, 0, 0, 0, 1)") {
        Matrix transform = Transform::shearing(0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
        Tuple p = Tuple::point(2.0, 3.0, 4.0);

        THEN("transform * p = point(2, 3, 7)") {
            CHECK(transform * p == Tuple::point(2.0, 3.0, 7.0));
        }
    }
}

SCENARIO("Individual transformations are applied in sequence", "[matrix][transform][bdd]") {
    GIVEN("p <- point(1, 0, 1)") {
        Tuple p = Tuple::point(1.0, 0.0, 1.0);
        Matrix A = Transform::rotation_x(pi / 2.0);
        Matrix B = Transform::scaling(5.0, 5.0, 5.0);
        Matrix C = Transform::translation(10.0, 5.0, 7.0);

        WHEN("p2 <- A * p") {
            Tuple p2 = A * p;

            THEN("p2 = point(1, -1, 0)") {
                CHECK(p2 == Tuple::point(1.0, -1.0, 0.0));
            }

            AND_WHEN("p3 <- B * p2") {
                Tuple p3 = B * p2;

                THEN("p3 = point(5, -5, 0)") {
                    CHECK(p3 == Tuple::point(5.0, -5.0, 0.0));
                }

                AND_WHEN("p4 <- C * p3") {
                    Tuple p4 = C * p3;

                    THEN("p4 = point(15, 0, 7)") {
                        CHECK(p4 == Tuple::point(15.0, 0.0, 7.0));
                    }
                }
            }
        }
    }
}

SCENARIO("Chained transformations must be applied in reverse order", "[matrix][transform][bdd]") {
    GIVEN("p <- point(1, 0, 1)") {
        Tuple p = Tuple::point(1.0, 0.0, 1.0);
        Matrix A = Transform::rotation_x(pi / 2.0);
        Matrix B = Transform::scaling(5.0, 5.0, 5.0);
        Matrix C = Transform::translation(10.0, 5.0, 7.0);

        WHEN("T <- C * B * A") {
            Matrix T = C * B * A;

            THEN("T * p = point(15, 0, 7)") {
                CHECK(T * p == Tuple::point(15.0, 0.0, 7.0));
            }
        }
    }
}

SCENARIO("The transformation matrix for the default orientation", "[matrix][transform][view][bdd]") {
    GIVEN("from <- point(0, 0, 0), to <- point(0, 0, -1), up <- vector(0, 1, 0)") {
        Tuple from = Tuple::point(0.0, 0.0, 0.0);
        Tuple to = Tuple::point(0.0, 0.0, -1.0);
        Tuple up = Tuple::vector(0.0, 1.0, 0.0);

        WHEN("t <- view_transform(from, to, up)") {
            Matrix t = Transform::view_transform(from, to, up);

            THEN("t = identity_matrix") {
                CHECK(t == identity_matrix(4));
            }
        }
    }
}

SCENARIO("A view transformation matrix looking in positive z direction", "[matrix][transform][view][bdd]") {
    GIVEN("from <- point(0, 0, 0), to <- point(0, 0, 1), up <- vector(0, 1, 0)") {
        Tuple from = Tuple::point(0.0, 0.0, 0.0);
        Tuple to = Tuple::point(0.0, 0.0, 1.0);
        Tuple up = Tuple::vector(0.0, 1.0, 0.0);

        WHEN("t <- view_transform(from, to, up)") {
            Matrix t = Transform::view_transform(from, to, up);

            THEN("t = scaling(-1, 1, -1)") {
                CHECK(t == Transform::scaling(-1.0, 1.0, -1.0));
            }
        }
    }
}

SCENARIO("The view transformation moves the world", "[matrix][transform][view][bdd]") {
    GIVEN("from <- point(0, 0, 8), to <- point(0, 0, 0), up <- vector(0, 1, 0)") {
        Tuple from = Tuple::point(0.0, 0.0, 8.0);
        Tuple to = Tuple::point(0.0, 0.0, 0.0);
        Tuple up = Tuple::vector(0.0, 1.0, 0.0);

        WHEN("t <- view_transform(from, to, up)") {
            Matrix t = Transform::view_transform(from, to, up);

            THEN("t = translation(0, 0, -8)") {
                CHECK(t == Transform::translation(0.0, 0.0, -8.0));
            }
        }
    }
}

SCENARIO("An arbitrary view transformation", "[matrix][transform][view][bdd]") {
    GIVEN("from <- point(1, 3, 2), to <- point(4, -2, 8), up <- vector(1, 1, 0)") {
        Tuple from = Tuple::point(1.0, 3.0, 2.0);
        Tuple to = Tuple::point(4.0, -2.0, 8.0);
        Tuple up = Tuple::vector(1.0, 1.0, 0.0);

        WHEN("t <- view_transform(from, to, up)") {
            Matrix t = Transform::view_transform(from, to, up);

            THEN("t is the expected 4x4 transformation matrix") {
                Matrix expected = identity_matrix(4);
                expected(0, 0) = -0.50709;
                expected(0, 1) = 0.50709;
                expected(0, 2) = 0.67612;
                expected(0, 3) = -2.36643;
                expected(1, 0) = 0.76772;
                expected(1, 1) = 0.60609;
                expected(1, 2) = 0.12122;
                expected(1, 3) = -2.82843;
                expected(2, 0) = -0.35857;
                expected(2, 1) = 0.59761;
                expected(2, 2) = -0.71714;
                expected(2, 3) = 0.00000;
                CHECK(t == expected);
            }
        }
    }
}

