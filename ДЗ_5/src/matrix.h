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

inline double norm(const std::vector<double>& v) {
    double sum = 0.0;

    for (int i = 0; i < (int)v.size(); i++) {
        sum += v[i] * v[i];
    }

    return sqrt(sum);
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

Result mpi(
    const SparseMatrix& A,
    const std::vector<double>& b,
    double tau,
    double eps,
    int max_iter
);

Result chebyshev(
    const SparseMatrix& A,
    const std::vector<double>& b,
    double lambda_min,
    double lambda_max,
    double eps,
    int max_iter
);

Result jacobi(
    const SparseMatrix& A,
    const std::vector<double>& b,
    double eps,
    int max_iter
);

Result gauss_seidel(
    const SparseMatrix& A,
    const std::vector<double>& b,
    double eps,
    int max_iter
);
