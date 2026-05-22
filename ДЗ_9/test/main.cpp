#include "../src/matrix.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

void print_result(
    const std::string& name,
    const Result& result
) {
    std::cout << name << std::endl;
    std::cout << "iterations: " << result.iterations << std::endl;
    std::cout << "residual norm: " << result.residual_norm << std::endl;
    std::cout << "time ms: " << result.time_ms << std::endl;
    std::cout << std::endl;
}

void save_history(
    const std::string& filename,
    const Result& cg_result,
    const Result& pcg_result
) {
    std::ofstream out(filename);

    out << "method,iteration,residual,time_ms\n";

    for (int i = 0; i < (int)cg_result.residuals.size(); i++) {
        out << "cg,"
            << i + 1 << ","
            << cg_result.residuals[i] << ","
            << cg_result.times[i] << "\n";
    }

    for (int i = 0; i < (int)pcg_result.residuals.size(); i++) {
        out << "pcg_cholesky,"
            << i + 1 << ","
            << pcg_result.residuals[i] << ","
            << pcg_result.times[i] << "\n";
    }

    out.close();
}

void print_levels_part(
    const std::vector<std::vector<int>>& levels,
    int count
) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            std::cout << levels[i][j] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

int main() {
    int m = 30;

    SparseMatrix A_negative = make_negative_poisson_matrix(m);
    SparseMatrix A = change_sign(A_negative);

    std::vector<double> b(A.n, 1.0);

    std::vector<std::vector<int>> levels = level_matrix(A);

    SparseMatrix L = incomplete_cholesky_0(A);

    double eps = 1e-8;
    int max_iter = 10000;

    Result cg_result = conjugate_gradient(
        A,
        b,
        eps,
        max_iter
    );

    Result pcg_result = preconditioned_conjugate_gradient(
        A,
        L,
        b,
        eps,
        max_iter
    );

    std::cout << "Level matrix first 10 x 10:" << std::endl;
    print_levels_part(levels, 10);

    std::cout << "IC0 nonzero count: " << L.values.size() << std::endl;
    std::cout << std::endl;

    print_result("Conjugate Gradient", cg_result);
    print_result("Preconditioned Conjugate Gradient", pcg_result);

    save_history(
        "history.csv",
        cg_result,
        pcg_result
    );

    return 0;
}
