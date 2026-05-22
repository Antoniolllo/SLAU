#include <iostream>
#include <vector>

#include "../src/matrix.h"

int main() {
    std::vector<std::vector<double>> matrix = {
        {4, -1, 0, 0, 0},
        {-1, 4, -1, 0, 0},
        {0, -1, 4, -1, 0},
        {0, 0, -1, 4, -1},
        {0, 0, 0, -1, 4}
    };

    SparseMatrix A = make_sparse_matrix(matrix);

    std::vector<double> b = {1, 1, 1, 1, 1};

    double eps = 1e-7;
    int max_iter = 1000;

    Result r1 = mpi(A, b, 0.25, eps, max_iter);
    Result r2 = chebyshev(A, b, 2.0, 6.0, eps, max_iter);
    Result r3 = jacobi(A, b, eps, max_iter);
    Result r4 = gauss_seidel(A, b, eps, max_iter);

    std::cout << "method iterations residual time_ms\n";

    std::cout << "mpi "
              << r1.iterations << " "
              << r1.residual_norm << " "
              << r1.time_ms << "\n";

    std::cout << "chebyshev "
              << r2.iterations << " "
              << r2.residual_norm << " "
              << r2.time_ms << "\n";

    std::cout << "jacobi "
              << r3.iterations << " "
              << r3.residual_norm << " "
              << r3.time_ms << "\n";

    std::cout << "gauss_seidel "
              << r4.iterations << " "
              << r4.residual_norm << " "
              << r4.time_ms << "\n";

    return 0;
}
