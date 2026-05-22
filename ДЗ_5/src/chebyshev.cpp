#include "matrix.h"

#include <chrono>
#include <cmath>

Result chebyshev(
    const SparseMatrix& A,
    const std::vector<double>& b,
    double lambda_min,
    double lambda_max,
    double eps,
    int max_iter
) {
    auto time_start = std::chrono::high_resolution_clock::now();

    std::vector<double> x(A.n, 0.0);

    double d = (lambda_max + lambda_min) / 2.0;
    double c = (lambda_max - lambda_min) / 2.0;

    int iter = 0;
    double res_norm = 0.0;

    Result answer;

    for (iter = 1; iter <= max_iter; iter++) {
        std::vector<double> r = residual(A, x, b);

        double tau =
            1.0 / (d - c * cos((2.0 * iter - 1.0) * M_PI / (2.0 * max_iter)));

        for (int i = 0; i < A.n; i++) {
            x[i] = x[i] + tau * r[i];
        }

        res_norm = norm(r);

        auto current_time = std::chrono::high_resolution_clock::now();
        double time_ms =
            std::chrono::duration<double, std::milli>(current_time - time_start).count();

        answer.residuals.push_back(res_norm);
        answer.times.push_back(time_ms);

        if (res_norm < eps) {
            break;
        }
    }

    std::vector<double> r = residual(A, x, b);
    res_norm = norm(r);

    auto time_finish = std::chrono::high_resolution_clock::now();
    double time_ms =
        std::chrono::duration<double, std::milli>(time_finish - time_start).count();

    answer.x = x;
    answer.iterations = iter;
    answer.residual_norm = res_norm;
    answer.time_ms = time_ms;

    return answer;
}
