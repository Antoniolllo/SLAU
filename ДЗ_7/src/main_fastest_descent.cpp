#include <iostream>
#include <vector>

std::vector<double> steepestDescent(
    const std::vector<std::vector<double>>& A,
    const std::vector<double>& b,
    const std::vector<double>& x0,
    int maxIter,
    double eps
);

int main() {
    std::vector<std::vector<double>> A = {
        {4, 1},
        {1, 3}
    };

    std::vector<double> b = {1, 2};
    std::vector<double> x0 = {0, 0};

    auto x = steepestDescent(A, b, x0, 1000, 1e-6);

    for (double xi : x) {
        std::cout << xi << " ";
    }
    std::cout << std::endl;

    return 0;
}
