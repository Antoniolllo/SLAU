#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "householder_algorithm.hpp"

int main() {
        int n;
        std::cin >> n;

        dense_matrix_householder<double> A(n, n);
        A.fill();

        std::vector<double> b(n);
        for (int i = 0; i < n; ++i) {
                std::cin >> b[i];
        }

        dense_matrix_householder<double> Q(n, n);
        dense_matrix_householder<double> R(n, n);

        A.martix_QR(Q, R);

        // y = Q^T b
        std::vector<double> y(n, 0);
        for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                        y[i] += Q.get(j, i) * b[j];
                }
        }

        // обратный ход: R x = y
        std::vector<double> x(n, 0);


	for (int i = n - 1; i >= 0; --i) {
        	double right_part = y[i];

        	for (int j = i + 1; j < n; ++j) {
                	right_part -= R.get(i, j) * x[j];
        	}

        	x[i] = right_part / R.get(i, i);
	}

        std::cout << "solution:\n";
        for (int i = 0; i < n; ++i) {
                std::cout << x[i] << " ";
        }
        std::cout << "\n";

        return 0;
}
