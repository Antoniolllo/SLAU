#include <iostream>
#include <cmath>
#include <vector>

// матрицу храним построчно

std::vector<double> conjugateGradient(
        const std::vector<std::vector<double>>& A,
        const std::vector<double>& b,
        const std::vector<double>& x0,
        int maxIter,
        double eps) {

    int n = b.size();

    std::vector<double> x = x0;
    std::vector<double> r(n);
    std::vector<double> d(n);

    // r0 = b - A * x0
    std::vector<double> Ax(n, 0.0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Ax[i] += A[i][j] * x[j];
        }
    }

    for (int i = 0; i < n; i++) {
        r[i] = b[i] - Ax[i];
        d[i] = r[i];
    }

    for (int k = 0; k < maxIter; k++) {

        double rr = 0.0;
        for (int i = 0; i < n; i++) {
            rr += r[i] * r[i];
        }

        if (rr < eps * eps) {
            break;
        }

        // Ad = A * d
        std::vector<double> Ad(n, 0.0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                Ad[i] += A[i][j] * d[j];
            }
        }

        double dAd = 0.0;
        for (int i = 0; i < n; i++) {
            dAd += d[i] * Ad[i];
        }

        if (std::abs(dAd) < 1e-15) {
            break;
        }

        double alpha = rr / dAd;

        // x_{k+1} = x_k + alpha * d_k
        for (int i = 0; i < n; i++) {
            x[i] += alpha * d[i];
        }

        // r_{k+1} = r_k - alpha * A d_k
        std::vector<double> r_new(n);

        for (int i = 0; i < n; i++) {
            r_new[i] = r[i] - alpha * Ad[i];
        }

        double rr_new = 0.0;
        for (int i = 0; i < n; i++) {
            rr_new += r_new[i] * r_new[i];
        }

        double beta = rr_new / rr;

        // d_{k+1} = r_{k+1} + beta * d_k
        for (int i = 0; i < n; i++) {
            d[i] = r_new[i] + beta * d[i];
        }

        r = r_new;
    }

    return x;
}
