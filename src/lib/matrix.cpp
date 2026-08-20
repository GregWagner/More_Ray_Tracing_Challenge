#include "matrix.hpp"

#include <cmath>
#include <stdexcept>

namespace rtc {
    // Compare two doubles with epsilon tolerance
    auto approxEqual(double a, double b, double eps) -> bool {
        return std::fabs(a - b) <= eps;
    }

    // Create an identity matrix of size n x n
    auto identity_matrix(int n) -> Matrix {
        Matrix m(n, n);
        for (int i = 0; i < n; ++i) {
            m(i, i) = 1.0;
        }
        return m;
    }

    // Transpose a matrix (swap rows and columns)
    auto transpose(const Matrix &m) -> Matrix {
        Matrix out(m.cols(), m.rows());
        for (int r{}; r < m.rows(); ++r) {
            for (int c{}; c < m.cols(); ++c) {
                out(c, r) = m(r, c);
            }
        }
        return out;
    }

    // Create a submatrix by removing a specific row and column
    auto submatrix(const Matrix &m, int remove_row, int remove_col) -> Matrix {
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

    // Calculate the determinant of a matrix
    auto determinant(const Matrix &m) -> double {
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

    // Calculate the minor of a matrix element (determinant of submatrix)
    auto minor(const Matrix &m, int row, int col) -> double {
        return determinant(submatrix(m, row, col));
    }

    // Calculate the cofactor of a matrix element (minor with sign)
    auto cofactor(const Matrix &m, int row, int col) -> double {
        const double mn = minor(m, row, col);
        if ((row + col) % 2 == 1) {
            return -mn;
        }
        return mn;
    }

    // Check if a matrix is invertible (non-zero determinant)
    auto is_invertible(const Matrix &m) -> bool {
        return !approxEqual(determinant(m), 0.0);
    }

    // Calculate the inverse of a matrix
    auto inverse(const Matrix &m) -> Matrix {
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
