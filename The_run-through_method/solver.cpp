#include "solver.hpp"
#include <vector>
#include <stdexcept>
#include <cmath> 

std::vector<double> solver(
    const std::vector<double>& a,
    const std::vector<double>& b,
    const std::vector<double>& c,
    const std::vector<double>& d
) {
    int n = b.size();

    std::vector<double> alfa(n);
    std::vector<double> betta(n);   ////  без n будет функция, а так вектор
    std::vector<double> x(n);

    for (int i = 0; i < n; ++i) {
        if (std::abs(b[i]) < std::abs(a[i]) + std::abs(c[i])) {
            throw std::runtime_error("Diagonal dominance condition failed.");
        }

    }

    // прямой ход
    alfa[0]  = -c[0] / b[0];
    betta[0] =  d[0] / b[0];    // в первый раз будет 2 слагаемых, потом 3 и для коффициентов альфа и бетта будут другие выражения

    for (int i = 0; i < n - 1; ++i) {
        alfa[i + 1]  = -c[i + 1] / (a[i + 1] * alfa[i] + b[i + 1]);
        betta[i + 1] = (d[i + 1] - a[i + 1] * betta[i]) / (a[i + 1] * alfa[i] + b[i + 1]);
    }

    // обратный ход
    x[n - 1] = betta[n - 1];

    for (int i = n - 2; i >= 0; --i) {
        x[i] = alfa[i] * x[i + 1] + betta[i];
    }

    return x;
}


