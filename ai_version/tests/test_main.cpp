#include "PixelMath.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Center coordinate calculations", "[pixel_math]") {
    SECTION("Standard 800x450 resolution") {
        constexpr auto center = PixelApp::calculateCenter(800, 450);

        REQUIRE(center.x == 400);
        REQUIRE(center.y == 225);
    }

    SECTION("Odd dimensions round down towards zero") {
        constexpr auto center = PixelApp::calculateCenter(801, 451);
       
        REQUIRE(center.x == 400);
        REQUIRE(center.y == 225);
    }
}

TEST_CASE("Screen boundary validation", "[pixel_math]") {
    SECTION("Valid inside coordinates") {
        REQUIRE(PixelApp::isWithinBounds({400, 225}, 800, 450));
        REQUIRE(PixelApp::isWithinBounds({0, 0}, 800, 450));
        REQUIRE(PixelApp::isWithinBounds({799, 449}, 800, 450));
    }

    SECTION("Out of bounds coordinates") {
        REQUIRE_FALSE(PixelApp::isWithinBounds({800, 225}, 800, 450));
        REQUIRE_FALSE(PixelApp::isWithinBounds({400, 450}, 800, 450));
        REQUIRE_FALSE(PixelApp::isWithinBounds({-1, 100}, 800, 450));
    }
}
