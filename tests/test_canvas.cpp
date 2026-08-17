#include <catch2/catch_test_macros.hpp>
#include <sstream>

#include "lib/canvas.hpp"
#include "lib/color.hpp"

using namespace rtc;

SCENARIO("Creating a canvas", "[canvas][bdd]") {
    GIVEN("c <- canvas(10, 20)") {
        Canvas c(10, 20);
        THEN("c.width = 10 and c.height = 20") {
            CHECK(c.width() == 10);
            CHECK(c.height() == 20);
        }
        THEN("every pixel is black (0, 0, 0)") {
            Color black(0.0, 0.0, 0.0);
            bool all_black = true;
            for (int y = 0; y < c.height(); ++y) {
                for (int x = 0; x < c.width(); ++x) {
                    if (!(c.pixel_at(x, y) == black)) {
                        all_black = false;
                        break;
                    }
                }
            }
            CHECK(all_black);
        }
    }
}

SCENARIO("Writing pixels to a canvas", "[canvas][bdd]") {
    GIVEN("c <- canvas(10, 20) and red <- color(1, 0, 0)") {
        Canvas c(10, 20);
        Color red(1.0, 0.0, 0.0);
        WHEN("write_pixel(c, 2, 3, red)") {
            c.write_pixel(2, 3, red);
            THEN("pixel_at(c, 2, 3) = red") {
                CHECK(c.pixel_at(2, 3) == red);
            }
        }
    }
}


SCENARIO("Constructing the PPM header", "[canvas][ppm][bdd]") {
    GIVEN("c <- canvas(5, 3)") {
        Canvas c(5, 3);

        WHEN("ppm <- canvas_to_ppm(c)") {
            std::string ppm = canvas_to_ppm(c);

            THEN("lines 1-3 of ppm form the valid header") {
                std::istringstream stream(ppm);
                std::string line1, line2, line3;

                std::getline(stream, line1);
                std::getline(stream, line2);
                std::getline(stream, line3);

                CHECK(line1 == "P3");
                CHECK(line2 == "5 3");
                CHECK(line3 == "255");
            }
        }
    }
}

SCENARIO("Constructing the PPM pixel data", "[canvas][ppm][bdd]") {
    GIVEN("c <- canvas(5, 3)") {
        Canvas c(5, 3);
        Color c1(1.5, 0.0, 0.0);
        Color c2(0.0, 0.5, 0.0);
        Color c3(-0.5, 0.0, 1.0);

        WHEN("pixels are written and canvas converted to PPM") {
            c.write_pixel(0, 0, c1);
            c.write_pixel(2, 1, c2);
            c.write_pixel(4, 2, c3);

            std::string ppm = canvas_to_ppm(c);

            THEN("lines 4-6 of ppm contain the formatted pixel data") {
                std::istringstream stream(ppm);
                std::string line;

                // Skip header (lines 1-3)
                std::getline(stream, line);
                std::getline(stream, line);
                std::getline(stream, line);

                std::string line4, line5, line6;
                std::getline(stream, line4);
                std::getline(stream, line5);
                std::getline(stream, line6);

                CHECK(line4 == "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
                CHECK(line5 == "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0");
                CHECK(line6 == "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");
            }
        }
    }
}

SCENARIO("Splitting long lines in PPM files", "[canvas][ppm][bdd]") {
    GIVEN("c <- canvas(10, 2)") {
        Canvas c(10, 2);
        Color c1(1.0, 0.8, 0.6);
        WHEN("every pixel of c is set to color(1, 0.8, 0.6) and converted to PPM") {
            for (int y = 0; y < c.height(); ++y) {
                for (int x = 0; x < c.width(); ++x) {
                    c.write_pixel(x, y, c1);
                }
            }
            std::string ppm = canvas_to_ppm(c);
            THEN("lines 4-7 split correctly within 70 characters") {
                std::istringstream stream(ppm);
                std::string line;

                // Skip header (lines 1-3)
                for (int i = 0; i < 3; ++i) {
                    std::getline(stream, line);
                }

                std::string line4, line5, line6, line7;
                std::getline(stream, line4);
                std::getline(stream, line5);
                std::getline(stream, line6);
                std::getline(stream, line7);

                CHECK(line4 == "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
                CHECK(line5 == "153 255 204 153 255 204 153 255 204 153 255 204 153");
                CHECK(line6 == "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
                CHECK(line7 == "153 255 204 153 255 204 153 255 204 153 255 204 153");
            }
        }
    }
}

SCENARIO("PPM files are terminated by a newline character", "[canvas][ppm][bdd]") {
    GIVEN("c <- canvas(5, 3)") {
        Canvas c(5, 3);
        WHEN("ppm <- canvas_to_ppm(c)") {
            std::string ppm = canvas_to_ppm(c);
            THEN("ppm ends with a newline character") {
                REQUIRE_FALSE(ppm.empty());
                CHECK(ppm.back() == '\n');
            }
        }
    }
}
