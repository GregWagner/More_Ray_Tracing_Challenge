#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <cmath>

#include "lib/matrix.hpp"   // adjust include paths to your project
#include "lib/tuple.hpp"    // if you have tuple
using namespace rtc;

using Catch::Approx;

static constexpr double EPS = 1e-3;

static void CHECK_MATRIX_EQ(const rtc::Matrix &a, const rtc::Matrix &b) {
    REQUIRE(a.rows() == b.rows());
    REQUIRE(a.cols() == b.cols());
    for (int r = 0; r < a.rows(); ++r) {
        for (int c = 0; c < a.cols(); ++c) {
            CAPTURE(r, c);
            CHECK(a[r][c] == Approx(b[r][c]).epsilon(EPS));
        }
    }
}

static rtc::Matrix makeMatrix(std::initializer_list<std::initializer_list<double> > vals) {
    const int rows = static_cast<int>(vals.size());
    const int cols = static_cast<int>(vals.begin()->size());
    rtc::Matrix m(rows, cols);
    int r{};
    for (auto &row: vals) {
        int c{};;
        for (auto &v: row) {
            m[r][c] = v;
            ++c;
        }
        ++r;
    }
    return m;
}

static rtc::Tuple makeTuple(double x, double y, double z, double w) {
    return Tuple(x, y, z, w);
}

SCENARIO("Constructing and inspecting a 4x4 matrix", "[matrix]") {
    auto M = makeMatrix({
        {1, 2, 3, 4},
        {5.5, 6.5, 7.5, 8.5},
        {9, 10, 11, 12},
        {13.5, 14.5, 15.5, 16.5}
    });
    CHECK(M[0][0] == Approx(1).epsilon(EPS));
    CHECK(M[0][3] == Approx(4).epsilon(EPS));
    CHECK(M[1][0] == Approx(5.5).epsilon(EPS));
    CHECK(M[1][2] == Approx(7.5).epsilon(EPS));
    CHECK(M[2][2] == Approx(11).epsilon(EPS));
    CHECK(M[3][0] == Approx(13.5).epsilon(EPS));
    CHECK(M[3][2] == Approx(15.5).epsilon(EPS));
}

SCENARIO("A 2x2 matrix ought to be representable", "[matrix]") {
    auto M = makeMatrix({
        {-3, 5},
        {1, -2}
    });
    CHECK(M[0][0] == Approx(-3).epsilon(EPS));
    CHECK(M[0][1] == Approx(5).epsilon(EPS));
    CHECK(M[1][0] == Approx(1).epsilon(EPS));
    CHECK(M[1][1] == Approx(-2).epsilon(EPS));
}

SCENARIO("A 3x3 matrix ought to be representable", "[matrix]") {
    auto M = makeMatrix({
        {-3, 5, 0},
        {1, -2, -7},
        {0, 1, 1}
    });
    CHECK(M[0][0] == Approx(-3).epsilon(EPS));
    CHECK(M[1][1] == Approx(-2).epsilon(EPS));
    CHECK(M[2][2] == Approx(1).epsilon(EPS));
}

SCENARIO("Matrix equality with identical matrices", "[matrix]") {
    auto A = makeMatrix({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    });
    auto B = makeMatrix({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    });
    CHECK(A == B);
}

SCENARIO("Matrix equality with different matrices", "[matrix]") {
    auto A = makeMatrix({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    });
    auto B = makeMatrix({
        {2, 3, 4, 5},
        {6, 7, 8, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    });
    CHECK(A != B);
}

SCENARIO("Multiplying two matrices", "[matrix]") {
    auto A = makeMatrix({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    });
    auto B = makeMatrix({
        {-2, 1, 2, 3},
        {3, 2, 1, -1},
        {4, 3, 6, 5},
        {1, 2, 7, 8}
    });
    auto expected = makeMatrix({
        {20, 22, 50, 48},
        {44, 54, 114, 108},
        {40, 58, 110, 102},
        {16, 26, 46, 42}
    });
    auto result = A * B;
    CHECK_MATRIX_EQ(result, expected);
}

SCENARIO("A matrix multiplied by a tuple", "[matrix]") {
    auto A = makeMatrix({
        {1, 2, 3, 4},
        {2, 4, 4, 2},
        {8, 6, 4, 1},
        {0, 0, 0, 1}
    });
    auto b = makeTuple(1, 2, 3, 1);
    auto result = A * b;
    auto expected = makeTuple(18, 24, 33, 1);
    CHECK(result == expected);
}

SCENARIO("Multiplying a matrix by the identity matrix", "[matrix]") {
    auto A = makeMatrix({
        {0, 1, 2, 4},
        {1, 2, 4, 8},
        {2, 4, 8, 16},
        {4, 8, 16, 32}
    });
    auto I = identity_matrix(4); // adjust if your function signature differs
    auto result = A * I;
    CHECK_MATRIX_EQ(result, A);
}

SCENARIO("Multiplying the identity matrix by a tuple", "[matrix]") {
    auto a = makeTuple(1, 2, 3, 4);
    auto I = identity_matrix(4);
    auto result = I * a;
    CHECK(result == a);
}

SCENARIO("Transposing a matrix", "[matrix]") {
    auto A = makeMatrix({
        {0, 9, 3, 0},
        {9, 8, 0, 8},
        {1, 8, 5, 3},
        {0, 0, 5, 8}
    });
    auto expected = makeMatrix({
        {0, 9, 1, 0},
        {9, 8, 8, 0},
        {3, 0, 5, 5},
        {0, 8, 3, 8}
    });
    auto result = transpose(A);
    CHECK_MATRIX_EQ(result, expected);
}

SCENARIO("Transposing the identity matrix", "[matrix]") {
    auto I = identity_matrix(4);
    auto result = transpose(I);
    CHECK_MATRIX_EQ(result, I);
}

SCENARIO("Calculating the determinant of a 2x2 matrix", "[matrix][determinant]") {
    auto A = makeMatrix({
        {1, 5},
        {-3, 2}
    });
    CHECK(determinant(A) == Approx(17).epsilon(EPS));
}

SCENARIO("A submatrix of a 3x3 matrix is a 2x2 matrix", "[matrix]") {
    auto A = makeMatrix({
        {1, 5, 0},
        {-3, 2, 7},
        {0, 6, -3}
    });
    auto result = submatrix(A, 0, 2);
    auto expected = makeMatrix({
        {-3, 2},
        {0, 6}
    });
    CHECK_MATRIX_EQ(result, expected);
}

SCENARIO("A submatrix of a 4x4 matrix is a 3x3 matrix", "[matrix]") {
    auto A = makeMatrix({
        {-6, 1, 1, 6},
        {-8, 5, 8, 6},
        {-1, 0, 8, 2},
        {-7, 1, -1, 1}
    });
    auto result = submatrix(A, 2, 1);
    auto expected = makeMatrix({
        {-6, 1, 6},
        {-8, 8, 6},
        {-7, -1, 1}
    });
    CHECK_MATRIX_EQ(result, expected);
}

SCENARIO("Calculating a minor of a 3x3 matrix", "[matrix][determinant]") {
    auto A = makeMatrix({
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}
    });
    auto B = submatrix(A, 1, 0);
    CHECK(determinant(B) == Approx(25).epsilon(EPS));
    CHECK(minor(A, 1, 0) == Approx(25).epsilon(EPS));
}

SCENARIO("Calculating a cofactor of a 3x3 matrix", "[matrix][determinant]") {
    auto A = makeMatrix({
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}
    });
    CHECK(minor(A, 0, 0) == Approx(-12).epsilon(EPS));
    CHECK(cofactor(A, 0, 0) == Approx(-12).epsilon(EPS));
    CHECK(minor(A, 1, 0) == Approx(25).epsilon(EPS));
    CHECK(cofactor(A, 1, 0) == Approx(-25).epsilon(EPS));
}

SCENARIO("Calculating the determinant of a 3x3 matrix", "[matrix][determinant]") {
    auto A = makeMatrix({
        {1, 2, 6},
        {-5, 8, -4},
        {2, 6, 4}
    });

    CHECK(cofactor(A, 0, 0) == Approx(56).epsilon(EPS));
    CHECK(cofactor(A, 0, 1) == Approx(12).epsilon(EPS));
    CHECK(cofactor(A, 0, 2) == Approx(-46).epsilon(EPS));
    CHECK(determinant(A) == Approx(-196).epsilon(EPS));
}

SCENARIO("Calculating the determinant of a 4x4 matrix", "[matrix][determinant]") {
    auto A = makeMatrix({
        {-2, -8, 3, 5},
        {-3, 1, 7, 3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9}
    });

    CHECK(cofactor(A, 0, 0) == Approx(690).epsilon(EPS));
    CHECK(cofactor(A, 0, 1) == Approx(447).epsilon(EPS));
    CHECK(cofactor(A, 0, 2) == Approx(210).epsilon(EPS));
    CHECK(cofactor(A, 0, 3) == Approx(51).epsilon(EPS));
    CHECK(determinant(A) == Approx(-4071).epsilon(EPS));
}

SCENARIO("Testing an invertible matrix for invertibility", "[matrix]") {
    auto A = makeMatrix({
        {6, 4, 4, 4},
        {5, 5, 7, 6},
        {4, -9, 3, -7},
        {9, 1, 7, -6}
    });

    CHECK(determinant(A) == Approx(-2120).epsilon(EPS));
    CHECK(is_invertible(A)); // adjust name if needed
}

SCENARIO("Testing a noninvertible matrix for invertibility", "[matrix]") {
    auto A = makeMatrix({
        {-4, 2, -2, -3},
        {9, 6, 2, 6},
        {0, -5, 1, -5},
        {0, 0, 0, 0}
    });

    CHECK(determinant(A) == Approx(0).epsilon(EPS));
    CHECK_FALSE(is_invertible(A));
}

SCENARIO("Calculating the inverse of a matrix", "[matrix]") {
    auto A = makeMatrix({
        {-5, 2, 6, -8},
        {1, -5, 1, 8},
        {7, 7, -6, -7},
        {1, -3, 7, 4}
    });

    auto B = inverse(A); // adjust name if needed

    CHECK(determinant(A) == Approx(532).epsilon(EPS));
    CHECK(cofactor(A, 2, 3) == Approx(-160).epsilon(EPS));
    CHECK(B[3][2] == Approx(-160.0 / 532.0).epsilon(EPS));
    CHECK(cofactor(A, 3, 2) == Approx(105).epsilon(EPS));
    CHECK(B[2][3] == Approx(105.0 / 532.0).epsilon(EPS));

    auto expected = makeMatrix({
        {0.21805, 0.45113, 0.24060, -0.04511},
        {-0.80827, -1.45677, -0.44361, 0.52068},
        {-0.07895, -0.22368, -0.05263, 0.19737},
        {-0.52256, -0.81391, -0.30075, 0.30639}
    });

    CHECK_MATRIX_EQ(B, expected);
}

SCENARIO("Calculating the inverse of another matrix", "[matrix]") {
    auto A = makeMatrix({
        {8, -5, 9, 2},
        {7, 5, 6, 1},
        {-6, 0, 9, 6},
        {-3, 0, -9, -4}
    });

    auto result = inverse(A);

    auto expected = makeMatrix({
        {-0.15385, -0.15385, -0.28205, -0.53846},
        {-0.07692, 0.12308, 0.02564, 0.03077},
        {0.35897, 0.35897, 0.43590, 0.92308},
        {-0.69231, -0.69231, -0.76923, -1.92308}
    });

    CHECK_MATRIX_EQ(result, expected);
}

SCENARIO("Calculating the inverse of a third matrix", "[matrix]") {
    auto A = makeMatrix({
        {9, 3, 0, 9},
        {-5, -2, -6, -3},
        {-4, 9, 6, 4},
        {-7, 6, 6, 2}
    });

    auto result = inverse(A);

    auto expected = makeMatrix({
        {-0.04074, -0.07778, 0.14444, -0.22222},
        {-0.07778, 0.03333, 0.36667, -0.33333},
        {-0.02901, -0.14630, -0.10926, 0.12963},
        {0.17778, 0.06667, -0.26667, 0.33333}
    });

    CHECK_MATRIX_EQ(result, expected);
}

SCENARIO("Multiplying a product by its inverse", "[matrix]") {
    auto A = makeMatrix({
        {3, -9, 7, 3},
        {3, -8, 2, -9},
        {-4, 4, 4, 1},
        {-6, 5, -1, 1}
    });

    auto B = makeMatrix({
        {8, 2, 2, 2},
        {3, -1, 7, 0},
        {7, 0, 5, 4},
        {6, -2, 0, 5}
    });

    auto C = A * B;
    auto result = C * inverse(B);

    CHECK_MATRIX_EQ(result, A);
}
