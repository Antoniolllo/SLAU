#include "../src/matrix.h"

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

void print_vector(const std::vector<double>& x) {
    for (int i = 0; i < (int)x.size(); i++) {
        std::cout << std::fixed << std::setprecision(6) << x[i] << " ";
    }

    std::cout << "\n";
}

void print_result(const char* name, const Result& result) {
    std::cout << name << "\n";

    std::cout << "x = ";
    print_vector(result.x);

    std::cout << "iterations = " << result.iterations << "\n";
    std::cout << "residual norm = " << result.residual_norm << "\n";
    std::cout << "time = " << result.time_ms << " ms\n";

    std::cout << "\n";
}

void save_result(const char* filename, const Result& result) {
    std::ofstream fout(filename);

    fout << "iteration,residual,time_ms\n";

    for (int i = 0; i < (int)result.residuals.size(); i++) {
        fout << i + 1 << ","
             << result.residuals[i] << ","
             << result.times[i] << "\n";
    }

    fout.close();
}

void save_comparison(
    const Result& mpi_result,
    const Result& jacobi_result,
    const Result& gauss_seidel_result
) {
    std::ofstream fout("comparison.csv");

    fout << "method,iterations,time_ms,residual\n";

    fout << "MPI,"
         << mpi_result.iterations << ","
         << mpi_result.time_ms << ","
         << mpi_result.residual_norm << "\n";

    fout << "Jacobi,"
         << jacobi_result.iterations << ","
         << jacobi_result.time_ms << ","
         << jacobi_result.residual_norm << "\n";

    fout << "Gauss-Seidel,"
         << gauss_seidel_result.iterations << ","
         << gauss_seidel_result.time_ms << ","
         << gauss_seidel_result.residual_norm << "\n";

    fout.close();
}

int main() {
    std::vector<std::vector<double>> simple_matrix = {
        {4, -1, 0, 0},
        {-1, 4, -1, 0},
        {0, -1, 4, -1},
        {0, 0, -1, 4}
    };

    std::vector<double> b = {
        1, 2, 3, 4
    };

    SparseMatrix A = make_sparse_matrix(simple_matrix);

    double eps = 1e-8;
    int max_iter = 100000;
    double tau = 0.2;

    Result answer_mpi = mpi(A, b, tau, eps, max_iter);
    Result answer_jacobi = jacobi(A, b, eps, max_iter);
    Result answer_gauss_seidel = gauss_seidel(A, b, eps, max_iter);

    print_result("Method of simple iterations", answer_mpi);
    print_result("Jacobi method", answer_jacobi);
    print_result("Gauss-Seidel method", answer_gauss_seidel);

    save_result("mpi.csv", answer_mpi);
    save_result("jacobi.csv", answer_jacobi);
    save_result("gauss_seidel.csv", answer_gauss_seidel);

    save_comparison(answer_mpi, answer_jacobi, answer_gauss_seidel);

    std::cout << "Files were saved:\n";
    std::cout << "mpi.csv\n";
    std::cout << "jacobi.csv\n";
    std::cout << "gauss_seidel.csv\n";
    std::cout << "comparison.csv\n";

    return 0;
}
