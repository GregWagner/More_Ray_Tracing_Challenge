// matrix.hpp
// Matrix class for 2D matrix operations in ray tracing
// Supports matrix multiplication, transformation of tuples, and linear algebra operations
#pragma once

#include <array>
#include <vector>
#include <cmath>
#include <stdexcept>

#include "tuple.hpp"

namespace rtc {
    static constexpr double MATRIX_EPS = 1e-5; // Tolerance for floating-point comparisons

    // Compare two doubles with epsilon tolerance
    auto approxEqual(double a, double b, double eps = MATRIX_EPS) -> bool;

    // Matrix represents a 2D matrix of doubles for linear algebra operations.
    // Used for transformations, solving systems, and other ray tracing calculations.
    class Matrix {
    public:
        // Default constructor creates an empty matrix
        Matrix() = default;

        // Create a matrix with specified dimensions, initialized to zero
        Matrix(int r, int c)
            : r_(r), c_(c), data_(static_cast<size_t>(r) * static_cast<size_t>(c), 0.0) {
            if (r_ <= 0 || c_ <= 0) {
                throw std::invalid_argument("Matrix dimensions must be positive");
            }
        }

        // Get the number of rows in the matrix
        [[nodiscard]] auto rows() const noexcept -> int { return r_; }

        // Get the number of columns in the matrix
        [[nodiscard]] auto cols() const noexcept -> int { return c_; }

        // Access element at (row, col) using function call syntax: m(r, c)
        auto operator()(int r, int c) -> double & {
            return data_.at((static_cast<size_t>(r) * static_cast<size_t>(c_)) + static_cast<size_t>(c));
        }

        // Const access element at (row, col) using function call syntax: m(r, c)
        auto operator()(int r, int c) const -> double {
            return data_.at((static_cast<size_t>(r) * static_cast<size_t>(c_)) + static_cast<size_t>(c));
        }

        // RowProxy enables m[r][c] access syntax for non-const matrices
        class RowProxy {
        public:
            RowProxy(double *p, int cols) : p_(p), cols_(cols) {
            }

            auto operator[](int c) -> double & { return p_[c]; }

        private:
            double *p_;
            int cols_;
        };

        // ConstRowProxy enables m[r][c] access syntax for const matrices
        class ConstRowProxy {
        public:
            ConstRowProxy(const double *p, int cols) : p_(p), cols_(cols) {
            }

            auto operator[](int c) const -> const double & { return p_[c]; }

        private:
            const double *p_;
            int cols_;
        };

        // Access row r to enable m[r][c] syntax
        auto operator[](int r) -> RowProxy {
            return {data_.data() + (static_cast<size_t>(r) * static_cast<size_t>(c_)), c_};
        }

        // Const access row r to enable m[r][c] syntax
        auto operator[](int r) const -> ConstRowProxy {
            return {data_.data() + (static_cast<size_t>(r) * static_cast<size_t>(c_)), c_};
        }

        // Equality comparison using epsilon tolerance for floating-point values
        auto operator==(const Matrix &o) const -> bool {
            if (r_ != o.r_ || c_ != o.c_) {
                return false;
            }
            for (size_t i = 0; i < data_.size(); ++i) {
                if (!approxEqual(data_[i], o.data_[i])) return false;
            }
            return true;
        }

        // Inequality comparison
        auto operator!=(const Matrix &o) const noexcept -> bool { return !(*this == o); }

        // Matrix multiplication: this * rhs
        // Throws if dimensions are incompatible (this.cols != rhs.rows)
        auto operator*(const Matrix &rhs) const -> Matrix {
            if (c_ != rhs.r_) {
                throw std::invalid_argument("Matrix multiplication dimension mismatch");
            }
            Matrix out(r_, rhs.c_);
            for (int r = 0; r < r_; ++r) {
                for (int c = 0; c < rhs.c_; ++c) {
                    double sum = 0.0;
                    for (int k = 0; k < c_; ++k) {
                        sum += (*this)(r, k) * rhs(k, c);
                    }
                    out(r, c) = sum;
                }
            }
            return out;
        }

        // Matrix * Tuple multiplication for transforming points and vectors
        // Requires a 4x4 matrix for 3D transformations
        auto operator*(const Tuple &t) const -> Tuple {
            if (r_ != 4 || c_ != 4) {
                throw std::invalid_argument("Matrix*Tuple expects a 4x4 matrix");
            }
            const std::array<double, 4> v{t.x_value, t.y_value, t.z_value, t.w_value};

            std::array<double, 4> outv{0.0, 0.0, 0.0, 0.0};
            for (int row = 0; row < 4; ++row) {
                double sum = 0.0;
                for (int col = 0; col < 4; ++col) {
                    sum += (*this)(row, col) * v[static_cast<size_t>(col)];
                }
                outv[static_cast<size_t>(row)] = sum;
            }
            return Tuple{outv[0], outv[1], outv[2], outv[3]};
        }

    private:
        int r_;                    // Number of rows
        int c_;                    // Number of columns
        std::vector<double> data_; // Matrix data stored in row-major order
    };

    // ---- Linear algebra free functions ----

    // Create an identity matrix of size n x n
    // Identity matrix has 1s on the diagonal and 0s elsewhere
    auto identity_matrix(int n) -> Matrix;

    // Transpose a matrix (swap rows and columns)
    auto transpose(const Matrix &m) -> Matrix;

    // Create a submatrix by removing a specific row and column
    // Used for computing minors and cofactors
    auto submatrix(const Matrix &m, int remove_row, int remove_col) -> Matrix;

    // Calculate the determinant of a matrix
    // Requires a square matrix; throws otherwise
    auto determinant(const Matrix &m) -> double;

    // Calculate the minor of a matrix element
    // Minor = determinant of the submatrix formed by removing the element's row and column
    auto minor(const Matrix &m, int row, int col) -> double;

    // Calculate the cofactor of a matrix element
    // Cofactor = minor with sign based on position: (-1)^(row+col) * minor
    auto cofactor(const Matrix &m, int row, int col) -> double;

    // Check if a matrix is invertible (non-zero determinant)
    auto is_invertible(const Matrix &m) -> bool;

    // Calculate the inverse of a matrix
    // Throws if the matrix is not invertible (determinant = 0)
    auto inverse(const Matrix &m) -> Matrix;
} // namespace rtc
