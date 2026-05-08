#include <iostream>
#include <cmath>
#include <vector>

// матрицу храним построчно

std::vector<double> steepestDescent(
        const std::vector<std::vector<double>>& A,
        const std::vector<double>& b,
        const std::vector<double>& x0,
        int maxIter,
        double eps) {

    int n = b.size();
    std::vector<double> r(n);
    std::vector<double> x = x0;

    for (int k = 0; k < maxIter; k++) {

        std::vector<double> Ax(n, 0.0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                Ax[i] += A[i][j] * x[j];
            }
        }

        for (int m = 0; m < n; m++) {
            r[m] = b[m] - Ax[m];
        }

        // считаем alpha итое

        double s1 = 0.0;
        for (int i = 0; i < n; i++) {
            s1 += r[i] * r[i];
        }

        // считаем Ar = A * r

        std::vector<double> Ar(n, 0.0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                Ar[i] += A[i][j] * r[j];
            }
        }

        double s2 = 0.0;
        for (int i = 0; i < n; i++) {
            s2 += r[i] * Ar[i];
        }

	if (s1 < eps * eps) {
 		break;
	}

	if (std::abs(s2) < 1e-15) {
    		break;
	}

        double alpha = s1 / s2;

        // x^{i+1} = x^i + alpha * r^i

        for (int i = 0; i < n; i++) {
            x[i] += alpha * r[i];
        }

}
	return x;
}



