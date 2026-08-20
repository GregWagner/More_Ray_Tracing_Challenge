// matrix.hpp
#pragma once

#include <array>
#include <vector>
#include <cmath>
#include <stdexcept>

#include "tuple.hpp"

namespace rtc {
    static constexpr double MATRIX_EPS = 1e-5;

    inline auto approxEqual(double a, double b, double eps = MATRIX_EPS) -> bool {
        return std::fabs(a - b) <= eps;
    }

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

    inline auto identity_matrix(int n) -> Matrix {
        Matrix m(n, n);
        for (int i = 0; i < n; ++i) {
            m(i, i) = 1.0;
        }
        return m;
    }

    inline auto transpose(const Matrix &m) -> Matrix {
        Matrix out(m.cols(), m.rows());
        for (int r{}; r < m.rows(); ++r) {
            for (int c{}; c < m.cols(); ++c) {
                out(c, r) = m(r, c);
            }
        }
        return out;
    }

    inline auto submatrix(const Matrix &m, int remove_row, int remove_col) -> Matrix {
        Matrix out(m.rows() - 1, m.cols() - 1);
        int orow{};
        for (int r{}; r < m.rows(); ++r) {
            if (r == remove_row) {
                continue;
            }
            int ocol{};
            for (int c{}; c < m.cols(); ++c) {
                if (c == remove_col) {
                    continue;
                }
                out(orow, ocol) = m(r, c);
                ++ocol;
            }
            ++orow;
        }
        return out;
    }

    inline double determinant(const Matrix &m);

    inline auto minor(const Matrix &m, int row, int col) -> double {
        return determinant(submatrix(m, row, col));
    }

    inline auto cofactor(const Matrix &m, int row, int col) -> double {
        const double mn = minor(m, row, col);
        if ((row + col) % 2 == 1) {
            return -mn;
        }
        return mn;
    }

    inline auto determinant(const Matrix &m) -> double {
        if (m.rows() != m.cols()) {
            throw std::invalid_argument("Determinant requires a square matrix");
        }

        const int n = m.rows();
        if (n == 2) {
            return (m(0, 0) * m(1, 1)) - (m(0, 1) * m(1, 0));
        }

        double det = 0.0;
        for (int c = 0; c < n; ++c) {
            double sign = (c % 2 == 0) ? 1.0 : -1.0;
            det += sign * m(0, c) * minor(m, 0, c);
        }
        return det;
    }

    inline auto is_invertible(const Matrix &m) -> bool {
        return !approxEqual(determinant(m), 0.0);
    }

    inline auto inverse(const Matrix &m) -> Matrix {
        const double det = determinant(m);
        if (approxEqual(det, 0.0)) {
            throw std::domain_error("Matrix is not invertible");
        }

        const int n = m.rows();
        Matrix out(n, n);

        // out(r,c) = cofactor(m, c, r) / det  (transpose of cofactor matrix)
        for (int r{}; r < n; ++r) {
            for (int c{}; c < n; ++c) {
                out(r, c) = cofactor(m, c, r) / det;
            }
        }

        return out;
    }
} // namespace rtc
