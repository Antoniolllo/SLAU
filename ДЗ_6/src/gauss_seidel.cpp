#include "matrix.h"

#include <chrono>

Result gauss_seidel(
    const SparseMatrix& A,
    const std::vector<double>& b,
    double eps,
    int max_iter
) {
    auto time_start = std::chrono::high_resolution_clock::now();

    std::vector<double> x(A.n, 0.0);

    Result answer;
    int iter = 0;
    double res_norm = 0.0;

    for (iter = 1; iter <= max_iter; iter++) {
        for (int i = 0; i < A.n; i++) {
            double sum = 0.0;
            double diag = 1.0;

            for (int j = A.rows[i]; j < A.rows[i + 1]; j++) {
                int col = A.columns[j];

                if (col == i) {
                    diag = A.values[j];
                } else {
                    sum += A.values[j] * x[col];
                }
            }

            x[i] = (b[i] - sum) / diag;
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

    double time_ms =
        std::chrono::duration<double, std::milli>(
            time_finish - time_start
        ).count();

    answer.x = x;
    answer.iterations = iter;
    answer.residual_norm = res_norm;
    answer.time_ms = time_ms;

    return answer;
}
