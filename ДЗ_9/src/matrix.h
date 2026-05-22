#pragma once

#include <vector>
#include <cmath>

struct SparseMatrix {
    int n;

    std::vector<double> values;
    std::vector<int> columns;
    std::vector<int> rows;
};

struct Result {
    std::vector<double> x;

    int iterations;
    double residual_norm;
    double time_ms;

    std::vector<double> residuals;
    std::vector<double> times;
};

inline SparseMatrix make_sparse_matrix(
    const std::vector<std::vector<double>>& matrix
) {
    SparseMatrix A;

    A.n = matrix.size();
    A.rows.push_back(0);

    for (int i = 0; i < A.n; i++) {
        for (int j = 0; j < A.n; j++) {
            if (matrix[i][j] != 0.0) {
                A.values.push_back(matrix[i][j]);
                A.columns.push_back(j);
            }
        }

        A.rows.push_back(A.values.size());
    }

    return A;
}

inline SparseMatrix make_negative_poisson_matrix(int m) {
    int n = m * m;

    SparseMatrix A;
    A.n = n;
    A.rows.push_back(0);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            int row = i * m + j;

            if (i > 0) {
                A.values.push_back(1.0);
                A.columns.push_back((i - 1) * m + j);
            }

            if (j > 0) {
                A.values.push_back(1.0);
                A.columns.push_back(i * m + j - 1);
            }

            A.values.push_back(-4.0);
            A.columns.push_back(row);

            if (j + 1 < m) {
                A.values.push_back(1.0);
                A.columns.push_back(i * m + j + 1);
            }

            if (i + 1 < m) {
                A.values.push_back(1.0);
                A.columns.push_back((i + 1) * m + j);
            }

            A.rows.push_back(A.values.size());
        }
    }

    return A;
}

inline SparseMatrix change_sign(
    const SparseMatrix& A
) {
    SparseMatrix B = A;

    for (int i = 0; i < (int)B.values.size(); i++) {
        B.values[i] = -B.values[i];
    }

    return B;
}

inline double norm(
    const std::vector<double>& v
) {
    double sum = 0.0;

    for (int i = 0; i < (int)v.size(); i++) {
        sum += v[i] * v[i];
    }

    return sqrt(sum);
}

inline double dot(
    const std::vector<double>& a,
    const std::vector<double>& b
) {
    double sum = 0.0;

    for (int i = 0; i < (int)a.size(); i++) {
        sum += a[i] * b[i];
    }

    return sum;
}

inline std::vector<double> multiply(
    const SparseMatrix& A,
    const std::vector<double>& x
) {
    std::vector<double> result(A.n, 0.0);

    for (int i = 0; i < A.n; i++) {
        for (int j = A.rows[i]; j < A.rows[i + 1]; j++) {
            result[i] += A.values[j] * x[A.columns[j]];
        }
    }

    return result;
}

inline std::vector<double> residual(
    const SparseMatrix& A,
    const std::vector<double>& x,
    const std::vector<double>& b
) {
    std::vector<double> Ax = multiply(A, x);
    std::vector<double> r(A.n, 0.0);

    for (int i = 0; i < A.n; i++) {
        r[i] = b[i] - Ax[i];
    }

    return r;
}

inline double get_value(
    const SparseMatrix& A,
    int row,
    int col
) {
    for (int j = A.rows[row]; j < A.rows[row + 1]; j++) {
        if (A.columns[j] == col) {
            return A.values[j];
        }
    }

    return 0.0;
}

std::vector<std::vector<int>> level_matrix(
    const SparseMatrix& A
);

SparseMatrix incomplete_cholesky_0(
    const SparseMatrix& A
);

std::vector<double> apply_cholesky_preconditioner(
    const SparseMatrix& L,
    const std::vector<double>& r
);

Result conjugate_gradient(
    const SparseMatrix& A,
    const std::vector<double>& b,
    double eps,
    int max_iter
);

Result preconditioned_conjugate_gradient(
    const SparseMatrix& A,
    const SparseMatrix& L,
    const std::vector<double>& b,
    double eps,
    int max_iter
);
