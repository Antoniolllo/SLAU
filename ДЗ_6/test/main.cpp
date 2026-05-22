#include "../src/matrix.h"

#include <iostream>
#include <vector>
#include <fstream>

void print_result(
    const std::string& name,
    const Result& result
) {
    std::cout << name << std::endl;
    std::cout << "iterations: " << result.iterations << std::endl;
    std::cout << "residual norm: " << result.residual_norm << std::endl;
    std::cout << "time ms: " << result.time_ms << std::endl;

    std::cout << "x: ";
    for (int i = 0; i < (int)result.x.size(); i++) {
        std::cout << result.x[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void save_history(
    const std::string& filename,
    const Result& jacobi_result,
    const Result& gauss_result,
    const Result& sym_result,
    const Result& cheb_result
) {
    std::ofstream out(filename);

    out << "method,iteration,residual,time_ms\n";

    for (int i = 0; i < (int)jacobi_result.residuals.size(); i++) {
        out << "jacobi," << i + 1 << ","
            << jacobi_result.residuals[i] << ","
            << jacobi_result.times[i] << "\n";
    }

    for (int i = 0; i < (int)gauss_result.residuals.size(); i++) {
        out << "gauss_seidel," << i + 1 << ","
            << gauss_result.residuals[i] << ","
            << gauss_result.times[i] << "\n";
    }

    for (int i = 0; i < (int)sym_result.residuals.size(); i++) {
        out << "symmetric_gauss_seidel," << i + 1 << ","
            << sym_result.residuals[i] << ","
            << sym_result.times[i] << "\n";
    }

    for (int i = 0; i < (int)cheb_result.residuals.size(); i++) {
        out << "chebyshev_symmetric_gauss_seidel," << i + 1 << ","
            << cheb_result.residuals[i] << ","
            << cheb_result.times[i] << "\n";
    }

    out.close();
}

int main() {
    std::vector<std::vector<double>> matrix = {
        {10.0, 1.0, 1.0, 0.0},
        {1.0, 10.0, 1.0, 1.0},
        {1.0, 1.0, 10.0, 1.0},
        {0.0, 1.0, 1.0, 10.0}
    };

    std::vector<double> b = {
        12.0,
        13.0,
        13.0,
        12.0
    };

    SparseMatrix A = make_sparse_matrix(matrix);

    double eps = 1e-8;
    int max_iter = 1000;

    Result jacobi_result = jacobi(A, b, eps, max_iter);

    Result gauss_result = gauss_seidel(A, b, eps, max_iter);

    Result sym_result = symmetric_gauss_seidel(A, b, eps, max_iter);

    double lambda_min = 8.0;
    double lambda_max = 13.0;

    Result cheb_result = chebyshev_symmetric_gauss_seidel(
        A,
        b,
        lambda_min,
        lambda_max,
        eps,
        max_iter
    );

    print_result("Jacobi", jacobi_result);
    print_result("Gauss-Seidel", gauss_result);
    print_result("Symmetric Gauss-Seidel", sym_result);
    print_result("Chebyshev + Symmetric Gauss-Seidel", cheb_result);

    save_history(
        "history.csv",
        jacobi_result,
        gauss_result,
        sym_result,
        cheb_result
    );

    return 0;
}
