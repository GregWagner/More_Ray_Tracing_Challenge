#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "tuple.hpp"

using Catch::Matchers::WithinAbs;
using namespace rtc;

TEST_CASE("A tuple with w=1.0 is a point", "[tuple]") {
    Tuple a = Tuple(4.3, -4.2, 3.1, 1.0);

    REQUIRE_THAT(a.x, WithinAbs(4.3, 1e-5));
    REQUIRE_THAT(a.y, WithinAbs(-4.2, 1e-5));
    REQUIRE_THAT(a.z, WithinAbs(3.1, 1e-5));
    REQUIRE_THAT(a.w, WithinAbs(1.0, 1e-5));

    REQUIRE(a.is_point());
    REQUIRE_FALSE(a.is_vector());
}

TEST_CASE("A tuple with w=0.0 is a vector", "[tuple]") {
    Tuple a = Tuple(4.3, -4.2, 3.1, 0.0);

    REQUIRE_THAT(a.x, WithinAbs(4.3, 1e-5));
    REQUIRE_THAT(a.y, WithinAbs(-4.2, 1e-5));
    REQUIRE_THAT(a.z, WithinAbs(3.1, 1e-5));
    REQUIRE_THAT(a.w, WithinAbs(0.0, 1e-5));

    REQUIRE_FALSE(a.is_point());
    REQUIRE(a.is_vector());
}

TEST_CASE("point() creates tuples with w=1", "[tuple]") {
    Tuple p = point(4, -4, 3);

    REQUIRE(p.is_point());
    REQUIRE_FALSE(p.is_vector());
}

TEST_CASE("vector() creates tuples with w=0", "[tuple]") {
    Tuple v = vector(4, -4, 3);

    REQUIRE_FALSE(v.is_point());
    REQUIRE(v.is_vector());
}

TEST_CASE("Adding two tuples", "[tuple]") {
    Tuple a1 = Tuple(3, -2, 5, 1);
    Tuple a2 = Tuple(-2, 3, 1, 0);

    Tuple result = a1 + a2;

    REQUIRE_THAT(result.x, WithinAbs(1, 1e-5));
    REQUIRE_THAT(result.y, WithinAbs(1, 1e-5));
    REQUIRE_THAT(result.z, WithinAbs(6, 1e-5));
    REQUIRE_THAT(result.w, WithinAbs(1, 1e-5));
}

TEST_CASE("Subtracting two points", "[tuple]") {
    Tuple a1 = point(3, 2, 1);
    Tuple a2 = point(5, 6, 7);

    Tuple result = a1 - a2;

    REQUIRE_THAT(result.x, WithinAbs(-2, 1e-5));
    REQUIRE_THAT(result.y, WithinAbs(-4, 1e-5));
    REQUIRE_THAT(result.z, WithinAbs(-6, 1e-5));

    REQUIRE_FALSE(result.is_point());
    REQUIRE(result.is_vector());
}

TEST_CASE("Subtracting a vector from a point", "[tuple]") {
    Tuple p = point(3, 2, 1);
    Tuple v = vector(5, 6, 7);

    Tuple result = p - v;

    REQUIRE_THAT(result.x, WithinAbs(-2, 1e-5));
    REQUIRE_THAT(result.y, WithinAbs(-4, 1e-5));
    REQUIRE_THAT(result.z, WithinAbs(-6, 1e-5));

    REQUIRE(result.is_point());
    REQUIRE_FALSE(result.is_vector());
}

TEST_CASE("Subtracting two vectors", "[tuple]") {
    Tuple v1 = vector(3, 2, 1);
    Tuple v2 = vector(5, 6, 7);

    Tuple result = v1 - v2;

    REQUIRE_THAT(result.x, WithinAbs(-2, 1e-5));
    REQUIRE_THAT(result.y, WithinAbs(-4, 1e-5));
    REQUIRE_THAT(result.z, WithinAbs(-6, 1e-5));

    REQUIRE_FALSE(result.is_point());
    REQUIRE(result.is_vector());
}

TEST_CASE("Subtracting a vector from the zero vector", "[tuple]") {
    Tuple zero = vector(0, 0, 0);
    Tuple v = vector(1, -2, 3);

    Tuple result = zero - v;

    REQUIRE_THAT(result.x, WithinAbs(-1, 1e-5));
    REQUIRE_THAT(result.y, WithinAbs(2, 1e-5));
    REQUIRE_THAT(result.z, WithinAbs(-3, 1e-5));

    REQUIRE_FALSE(result.is_point());
    REQUIRE(result.is_vector());
}

TEST_CASE("Negating a tuple", "[tuple]") {
    Tuple a = Tuple(1, -2, 3, -4);

    Tuple result = -a;

    REQUIRE_THAT(result.x, WithinAbs(-1, 1e-5));
    REQUIRE_THAT(result.y, WithinAbs(2, 1e-5));
    REQUIRE_THAT(result.z, WithinAbs(-3, 1e-5));
    REQUIRE_THAT(result.w, WithinAbs(4, 1e-5));
}

TEST_CASE("Multiplying a tuple by a scalar", "[tuple]") {
    Tuple a = Tuple(1, -2, 3, -4);

    Tuple result = a * 3.5;

    REQUIRE_THAT(result.x, WithinAbs(3.5, 1e-5));
    REQUIRE_THAT(result.y, WithinAbs(-7, 1e-5));
    REQUIRE_THAT(result.z, WithinAbs(10.5, 1e-5));
    REQUIRE_THAT(result.w, WithinAbs(-14, 1e-5));
}

TEST_CASE("Multiplying a tuple by a fraction", "[tuple]") {
    Tuple a = Tuple(1, -2, 3, -4);

    Tuple result = a * 0.5;

    REQUIRE_THAT(result.x, WithinAbs(0.5, 1e-5));
    REQUIRE_THAT(result.y, WithinAbs(-1.0, 1e-5));
    REQUIRE_THAT(result.z, WithinAbs(1.5, 1e-5));
    REQUIRE_THAT(result.w, WithinAbs(-2.0, 1e-5));
}

TEST_CASE("Dividing a tuple by a scalar", "[tuple]") {
    Tuple a = Tuple(1, -2, 3, -4);

    Tuple result = a / 2;

    REQUIRE_THAT(result.x, WithinAbs(0.5, 1e-5));
    REQUIRE_THAT(result.y, WithinAbs(-1, 1e-5));
    REQUIRE_THAT(result.z, WithinAbs(1.5, 1e-5));
    REQUIRE_THAT(result.w, WithinAbs(-2, 1e-5));
}

TEST_CASE("Computing the magnitude of vector(1, 0, 0)", "[tuple]") {
    Tuple v = vector(1, 0, 0);

    double length = magnitude(v);

    REQUIRE_THAT(length, WithinAbs(1, 1e-5));
}

TEST_CASE("Computing the magnitude of vector(0, 1, 0)", "[tuple]") {
    Tuple v = vector(0, 1, 0);

    double length = magnitude(v);

    REQUIRE_THAT(length, WithinAbs(1, 1e-5));
}

TEST_CASE("Computing the magnitude of vector(0, 0, 1)", "[tuple]") {
    Tuple v = vector(0, 0, 1);

    double length = magnitude(v);

    REQUIRE_THAT(length, WithinAbs(1, 1e-5));
}

TEST_CASE("Computing the magnitude of vector(1, 2, 3)", "[tuple]") {
    Tuple v = vector(1, 2, 3);

    double length = magnitude(v);

    REQUIRE_THAT(length, WithinAbs(sqrt(14), 1e-5));
}


TEST_CASE("Computing the magnitude of vector(-1, -2, -3)", "[tuple]") {
    Tuple v = vector(-1, -2, -3);

    double length = magnitude(v);

    REQUIRE_THAT(length, WithinAbs(sqrt(14), 1e-5));
}

TEST_CASE("Normalizing vector(4, 0, 0) gives (1, 0, 0)", "[tuple]") {
    Tuple v = vector(4, 0, 0);

    Tuple normalized = normalize(v);

    REQUIRE_THAT(normalized.x, WithinAbs(1, 1e-5));
    REQUIRE_THAT(normalized.y, WithinAbs(0, 1e-5));
    REQUIRE_THAT(normalized.z, WithinAbs(0, 1e-5));

    REQUIRE(normalized.is_vector());
}


TEST_CASE("Normalizing vector(1, 2, 3)", "[tuple]") {
    Tuple v = vector(1, 2, 3);

    Tuple normalized = normalize(v);

    REQUIRE_THAT(normalized.x, WithinAbs(1 / sqrt(14), 1e-5));
    REQUIRE_THAT(normalized.y, WithinAbs(2 / sqrt(14), 1e-5));
    REQUIRE_THAT(normalized.z, WithinAbs(3 / sqrt(14), 1e-5));

    REQUIRE(normalized.is_vector());
}

TEST_CASE("The magnitude of a normalized vector", "tuple") {
    Tuple v = vector(1, 2, 3);

    Tuple normalized = normalize(v);
    double length = magnitude(normalized);

    REQUIRE_THAT(length, WithinAbs(1, 1e-5));
}
