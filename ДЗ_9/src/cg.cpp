#include "matrix.h"

#include <chrono>

Result conjugate_gradient(
    const SparseMatrix& A,
    const std::vector<double>& b,
    double eps,
    int max_iter
) {
    auto time_start = std::chrono::high_resolution_clock::now();

    std::vector<double> x(A.n, 0.0);
    std::vector<double> r = residual(A, x, b);
    std::vector<double> p = r;

    double rs_old = dot(r, r);

    Result answer;
    int iter = 0;
    double res_norm = norm(r);

    for (iter = 1; iter <= max_iter; iter++) {
        std::vector<double> Ap = multiply(A, p);

        double alpha = rs_old / dot(p, Ap);

        for (int i = 0; i < A.n; i++) {
            x[i] += alpha * p[i];
            r[i] -= alpha * Ap[i];
        }

        double rs_new = dot(r, r);
        res_norm = sqrt(rs_new);

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

        double beta = rs_new / rs_old;

        for (int i = 0; i < A.n; i++) {
            p[i] = r[i] + beta * p[i];
        }

        rs_old = rs_new;
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

Result preconditioned_conjugate_gradient(
    const SparseMatrix& A,
    const SparseMatrix& L,
    const std::vector<double>& b,
    double eps,
    int max_iter
) {
    auto time_start = std::chrono::high_resolution_clock::now();

    std::vector<double> x(A.n, 0.0);
    std::vector<double> r = residual(A, x, b);
    std::vector<double> z = apply_cholesky_preconditioner(L, r);
    std::vector<double> p = z;

    double rz_old = dot(r, z);

    Result answer;
    int iter = 0;
    double res_norm = norm(r);

    for (iter = 1; iter <= max_iter; iter++) {
        std::vector<double> Ap = multiply(A, p);

        double alpha = rz_old / dot(p, Ap);

        for (int i = 0; i < A.n; i++) {
            x[i] += alpha * p[i];
            r[i] -= alpha * Ap[i];
        }

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

        z = apply_cholesky_preconditioner(L, r);

        double rz_new = dot(r, z);
        double beta = rz_new / rz_old;

        for (int i = 0; i < A.n; i++) {
            p[i] = z[i] + beta * p[i];
        }

        rz_old = rz_new;
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
