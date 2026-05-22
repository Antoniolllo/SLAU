#include "matrix.h"

#include <cmath>

SparseMatrix incomplete_cholesky_0(
    const SparseMatrix& A
) {
    int n = A.n;

    std::vector<std::vector<double>> L(n, std::vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        for (int jj = A.rows[i]; jj < A.rows[i + 1]; jj++) {
            int j = A.columns[jj];

            if (j > i) {
                continue;
            }

            if (j < i) {
                double sum = 0.0;

                for (int k = 0; k < j; k++) {
                    sum += L[i][k] * L[j][k];
                }

                if (fabs(L[j][j]) < 1e-14) {
                    L[i][j] = 0.0;
                } else {
                    L[i][j] = (get_value(A, i, j) - sum) / L[j][j];
                }
            } else {
                double sum = 0.0;

                for (int k = 0; k < i; k++) {
                    sum += L[i][k] * L[i][k];
                }

                double value = get_value(A, i, i) - sum;

                if (value < 1e-14) {
                    value = 1e-14;
                }

                L[i][i] = sqrt(value);
            }
        }
    }

    SparseMatrix result;
    result.n = n;
    result.rows.push_back(0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (L[i][j] != 0.0) {
                result.values.push_back(L[i][j]);
                result.columns.push_back(j);
            }
        }

        result.rows.push_back(result.values.size());
    }

    return result;
}

std::vector<double> apply_cholesky_preconditioner(
    const SparseMatrix& L,
    const std::vector<double>& r
) {
    int n = L.n;

    std::vector<double> y(n, 0.0);
    std::vector<double> z(n, 0.0);

    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        double diag = 1.0;

        for (int j = L.rows[i]; j < L.rows[i + 1]; j++) {
            int col = L.columns[j];

            if (col < i) {
                sum += L.values[j] * y[col];
            }

            if (col == i) {
                diag = L.values[j];
            }
        }

        y[i] = (r[i] - sum) / diag;
    }

    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        double diag = 1.0;

        for (int row = i; row < n; row++) {
            for (int j = L.rows[row]; j < L.rows[row + 1]; j++) {
                int col = L.columns[j];

                if (col == i) {
                    if (row == i) {
                        diag = L.values[j];
                    } else {
                        sum += L.values[j] * z[row];
                    }
                }
            }
        }

        z[i] = (y[i] - sum) / diag;
    }

    return z;
}
