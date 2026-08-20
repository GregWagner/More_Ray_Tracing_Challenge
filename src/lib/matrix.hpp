// matrix.hpp
#pragma once

#include <array>
#include <vector>
#include <cmath>
#include <stdexcept>

#include "tuple.hpp"

namespace rtc {
    static constexpr double MATRIX_EPS = 1e-5;

    auto approxEqual(double a, double b, double eps = MATRIX_EPS) -> bool;

    class Matrix {
    public:
        Matrix() = default;

        Matrix(int r, int c)
            : r_(r), c_(c), data_(static_cast<size_t>(r) * static_cast<size_t>(c), 0.0) {
            if (r_ <= 0 || c_ <= 0) {
                throw std::invalid_argument("Matrix dimensions must be positive");
            }
        }

        [[nodiscard]] auto rows() const noexcept -> int { return r_; }
        [[nodiscard]] auto cols() const noexcept -> int { return c_; }

        // (r,c) access
        auto operator()(int r, int c) -> double & {
            // r and c are expected non-negative in your tests
            return data_.at((static_cast<size_t>(r) * static_cast<size_t>(c_)) + static_cast<size_t>(c));
        }

        auto operator()(int r, int c) const -> double {
            return data_.at((static_cast<size_t>(r) * static_cast<size_t>(c_)) + static_cast<size_t>(c));
        }

        // m[r][c] access
        class RowProxy {
        public:
            RowProxy(double *p, int cols) : p_(p), cols_(cols) {
            }

            auto operator[](int c) -> double & { return p_[c]; }

        private:
            double *p_;
            int cols_;
        };

        class ConstRowProxy {
        public:
            ConstRowProxy(const double *p, int cols) : p_(p), cols_(cols) {
            }

            auto operator[](int c) const -> const double & { return p_[c]; }

        private:
            const double *p_;
            int cols_;
        };

        auto operator[](int r) -> RowProxy {
            return {data_.data() + (static_cast<size_t>(r) * static_cast<size_t>(c_)), c_};
        }

        auto operator[](int r) const -> ConstRowProxy {
            return {data_.data() + (static_cast<size_t>(r) * static_cast<size_t>(c_)), c_};
        }

        auto operator==(const Matrix &o) const -> bool {
            if (r_ != o.r_ || c_ != o.c_) {
                return false;
            }
            for (size_t i = 0; i < data_.size(); ++i) {
                if (!approxEqual(data_[i], o.data_[i])) return false;
            }
            return true;
        }

        auto operator!=(const Matrix &o) const noexcept -> bool { return !(*this == o); }

        // matrix * matrix
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

        // matrix * tuple
        auto operator*(const Tuple &t) const -> Tuple {
            // Your tests use 4x4 matrices with Tuple(x,y,z,w)
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
        int r_{};
        int c_{};
        std::vector<double> data_; // row-major
    };

    // ---- required free functions ----

    auto identity_matrix(int n) -> Matrix;
    auto transpose(const Matrix &m) -> Matrix;
    auto submatrix(const Matrix &m, int remove_row, int remove_col) -> Matrix;
    auto determinant(const Matrix &m) -> double;
    auto minor(const Matrix &m, int row, int col) -> double;
    auto cofactor(const Matrix &m, int row, int col) -> double;
    auto is_invertible(const Matrix &m) -> bool;
    auto inverse(const Matrix &m) -> Matrix;
} // namespace rtc
