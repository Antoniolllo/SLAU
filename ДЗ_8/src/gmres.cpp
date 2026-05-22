#include "matrix.h"

#include <chrono>
#include <cmath>

std::vector<double> solve_linear_system(
    std::vector<std::vector<double>> A,
    std::vector<double> b
) {
    int n = b.size();

    for (int k = 0; k < n; k++) {
        double pivot = A[k][k];

        if (fabs(pivot) < 1e-14) {
            pivot = 1e-14;
        }

        for (int j = k; j < n; j++) {
            A[k][j] /= pivot;
        }
        b[k] /= pivot;

        for (int i = k + 1; i < n; i++) {
            double factor = A[i][k];

            for (int j = k; j < n; j++) {
                A[i][j] -= factor * A[k][j];
            }

            b[i] -= factor * b[k];
        }
    }

    std::vector<double> x(n, 0.0);

    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];

        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
    }

    return x;
}

std::vector<double> least_squares(
    const std::vector<std::vector<double>>& H,
    double beta,
    int k
) {
    std::vector<std::vector<double>> normal(k, std::vector<double>(k, 0.0));
    std::vector<double> rhs(k, 0.0);

    for (int i = 0; i < k; i++) {
        rhs[i] = beta * H[0][i];

        for (int j = 0; j < k; j++) {
            double sum = 0.0;

            for (int t = 0; t < k + 1; t++) {
                sum += H[t][i] * H[t][j];
            }

            normal[i][j] = sum;
        }
    }

    return solve_linear_system(normal, rhs);
}

Result gmres(
    const SparseMatrix& A,
    const std::vector<double>& b,
    double eps,
    int max_iter
) {
    auto time_start = std::chrono::high_resolution_clock::now();

    std::vector<double> x(A.n, 0.0);

    std::vector<double> r0 = residual(A, x, b);
    double beta = norm(r0);

    Result answer;
    int iter = 0;
    double res_norm = beta;

    if (beta < eps) {
        answer.x = x;
        answer.iterations = 0;
        answer.residual_norm = beta;
        answer.time_ms = 0.0;
        return answer;
    }
    std::vector<std::vector<double>> V(max_iter + 1, std::vector<double>(A.n, 0.0));

    std::vector<std::vector<double>> H(max_iter + 1, std::vector<double>(max_iter, 0.0));

    for (int i = 0; i < A.n; i++) {
        V[0][i] = r0[i] / beta;
    }

    for (iter = 1; iter <= max_iter; iter++) {
        int k = iter - 1;


        std::vector<double> w = multiply(A, V[k]);

        for (int j = 0; j <= k; j++) {
            H[j][k] = dot(w, V[j]);

            for (int i = 0; i < A.n; i++) {
                w[i] -= H[j][k] * V[j][i];
            }
        }

        H[k + 1][k] = norm(w);

        if (H[k + 1][k] > 1e-14 && iter < max_iter) {
            for (int i = 0; i < A.n; i++) {
                V[k + 1][i] = w[i] / H[k + 1][k];
            }
        }

        std::vector<double> y = least_squares(H, beta, iter);

        for (int i = 0; i < A.n; i++) {
            x[i] = 0.0;
        }

        for (int j = 0; j < iter; j++) {
            for (int i = 0; i < A.n; i++) {
                x[i] += V[j][i] * y[j];
            }
        }

        std::vector<double> r = residual(A, x, b);
        res_norm = norm(r);

        auto current_time = std::chrono::high_resolution_clock::now();
        double time_ms =
            std::chrono::duration<double, std::milli>(
                current_time - time_start
            ).count();

        answer.residuals.push_back(res_norm);
        answer.times.push_back(time_ms);

        if (res_norm < eps) {
            break;
        }
    }

    auto time_finish = std::chrono::high_resolution_clock::now();

    answer.x = x;
    answer.iterations = iter;
    answer.residual_norm = res_norm;
    answer.time_ms =
        std::chrono::duration<double, std::milli>(
            time_finish - time_start
        ).count();

    return answer;
}
