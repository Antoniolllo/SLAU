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

void save_one_history(
    std::ofstream& out,
    const std::string& name,
    const Result& result
) {
    for (int i = 0; i < (int)result.residuals.size(); i++) {
        out << name << ","
            << i + 1 << ","
            << result.residuals[i] << ","
            << result.times[i] << "\n";
    }
}

void save_history(
    const std::string& filename,
    const Result& jacobi_result,
    const Result& gauss_result,
    const Result& sym_result,
    const Result& gmres_result
) {
    std::ofstream out(filename);

    out << "method,iteration,residual,time_ms\n";

    save_one_history(out, "jacobi", jacobi_result);
    save_one_history(out, "gauss_seidel", gauss_result);
    save_one_history(out, "symmetric_gauss_seidel", sym_result);
    save_one_history(out, "gmres", gmres_result);

    out.close();
}

int main() {
    int m = 20;

    SparseMatrix A = make_poisson_matrix(m);

    std::vector<double> b(A.n, 1.0);

    double eps = 1e-8;

    int max_iter_simple = 5000;
    int max_iter_gmres = 100;

    Result jacobi_result = jacobi(
        A,
        b,
        eps,
        max_iter_simple
    );

    Result gauss_result = gauss_seidel(
        A,
        b,
        eps,
        max_iter_simple
    );

    Result sym_result = symmetric_gauss_seidel(
        A,
        b,
        eps,
        max_iter_simple
    );

    Result gmres_result = gmres(
        A,
        b,
        eps,
        max_iter_gmres
    );

    print_result("Jacobi", jacobi_result);
    print_result("Gauss-Seidel", gauss_result);
    print_result("Symmetric Gauss-Seidel", sym_result);
    print_result("GMRES", gmres_result);

    save_history(
        "history.csv",
        jacobi_result,
        gauss_result,
        sym_result,
        gmres_result
    );

    return 0;
}
