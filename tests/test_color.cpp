#include <catch2/catch_test_macros.hpp>
#include <sstream>

#include "lib/color.hpp"

using namespace rtc;

SCENARIO("Colors are (red, green, blue) tuples", "[color][bdd]") {
    GIVEN("c <- color(-0.5, 0.4, 1.7)") {
        Color c(-0.5, 0.4, 1.7);

        THEN("the colors match the input values") {
            CHECK(c == Color(-0.5, 0.4, 1.7));
        }
    }
}

SCENARIO("rgb() creates colors", "[color][bdd]") {
    GIVEN("c <- rgb(-0.5, 0.4, 1.7)") {
        auto c = Color::rgb(-0.5, 0.4, 1.7);

        THEN("c = color(-0.5, 0.4, 1.7)") {
            CHECK(c == Color(-0.5, 0.4, 1.7));
        }
    }
}

SCENARIO("Adding colors", "[color][bdd]") {
    GIVEN("c1 <- color(0.9, 0.6, 0.75)") {
        Color c1(0.9, 0.6, 0.75);

        AND_GIVEN("c2 <- color(0.7, 0.1, 1.0)") {
            Color c2(0.7, 0.1, 1.0);

            THEN("c1 + c2 = color(1.6, 0.7, 1.75)") {
                CHECK(c1 + c2 == Color(1.6, 0.7, 1.75));
            }
        }
    }
}

SCENARIO("Subtracting colors", "[color][bdd]") {
    GIVEN("c1 <- color(0.9, 0.6, 0.75)") {
        Color c1(0.9, 0.6, 0.75);

        AND_GIVEN("c2 <- color(0.7, 0.1, 0.25)") {
            Color c2(0.7, 0.1, 0.25);

            THEN("c1 - c2 = color(0.2, 0.5, 0.5)") {
                CHECK(c1 - c2 == Color(0.2, 0.5, 0.5));
            }
        }
    }
}

SCENARIO("Multiplying a color by a scalar", "[color][bdd]") {
    GIVEN("c <- color(0.2, 0.3, 0.4)") {
        Color c(0.2, 0.3, 0.4);

        THEN("c * 2 = color(0.4, 0.6, 0.8)") {
            CHECK(c * 2.0 == Color(0.4, 0.6, 0.8));
        }
    }
}

SCENARIO("Dividing a color by a scalar", "[color][bdd]") {
    GIVEN("c <- color(0.4, 0.6, 0.8)") {
        Color c(0.4, 0.6, 0.8);

        THEN("c / 2 = color(0.2, 0.3, 0.4)") {
            CHECK(c / 2.0 == Color(0.2, 0.3, 0.4));
        }
    }
}

SCENARIO("Multiplying colors", "[color][bdd]") {
    GIVEN("c1 <- color(1, 0.2, 0.4)") {
        Color c1(1, 0.2, 0.4);

        AND_GIVEN("c2 <- color(0.9, 1, 0.1)") {
            Color c2(0.9, 1, 0.1);

            THEN("c1 * c2 = color(0.9, 0.2, 0.04)") {
                CHECK(c1 * c2 == Color(0.9, 0.2, 0.04));
            }
        }
    }
}

SCENARIO("Compound assignment addition", "[color][bdd]") {
    GIVEN("c1 <- color(0.9, 0.6, 0.75)") {
        Color c1(0.9, 0.6, 0.75);

        AND_GIVEN("c2 <- color(0.7, 0.1, 1.0)") {
            Color c2(0.7, 0.1, 1.0);

            WHEN("c1 += c2") {
                c1 += c2;

                THEN("c1 = color(1.6, 0.7, 1.75)") {
                    CHECK(c1 == Color(1.6, 0.7, 1.75));
                }
            }
        }
    }
}

SCENARIO("Compound assignment subtraction", "[color][bdd]") {
    GIVEN("c1 <- color(0.9, 0.6, 0.75)") {
        Color c1(0.9, 0.6, 0.75);

        AND_GIVEN("c2 <- color(0.7, 0.1, 0.25)") {
            Color c2(0.7, 0.1, 0.25);

            WHEN("c1 -= c2") {
                c1 -= c2;

                THEN("c1 = color(0.2, 0.5, 0.5)") {
                    CHECK(c1 == Color(0.2, 0.5, 0.5));
                }
            }
        }
    }
}

SCENARIO("Compound assignment multiplication by scalar", "[color][bdd]") {
    GIVEN("c <- color(0.2, 0.3, 0.4)") {
        Color c(0.2, 0.3, 0.4);

        WHEN("c *= 2") {
            c *= 2.0;

            THEN("c = color(0.4, 0.6, 0.8)") {
                CHECK(c == Color(0.4, 0.6, 0.8));
            }
        }
    }
}

SCENARIO("Compound assignment multiplication by color", "[color][bdd]") {
    GIVEN("c1 <- color(1, 0.2, 0.4)") {
        Color c1(1, 0.2, 0.4);

        AND_GIVEN("c2 <- color(0.9, 1, 0.1)") {
            Color c2(0.9, 1, 0.1);

            WHEN("c1 *= c2") {
                c1 *= c2;

                THEN("c1 = color(0.9, 0.2, 0.04)") {
                    CHECK(c1 == Color(0.9, 0.2, 0.04));
                }
            }
        }
    }
}

SCENARIO("Compound assignment division by scalar", "[color][bdd]") {
    GIVEN("c <- color(0.4, 0.6, 0.8)") {
        Color c(0.4, 0.6, 0.8);

        WHEN("c /= 2") {
            c /= 2.0;

            THEN("c = color(0.2, 0.3, 0.4)") {
                CHECK(c == Color(0.2, 0.3, 0.4));
            }
        }
    }
}

SCENARIO("Stream output of a color", "[color][bdd]") {
    GIVEN("a color (1, -0.5, 0.25)") {
        Color c(1, -0.5, 0.25);

        WHEN("streamed to output") {
            std::ostringstream oss;
            oss << c;

            THEN("it outputs the correct format") {
                CHECK(oss.str() == "Color(1, -0.5, 0.25)");
            }
        }
    }
}
