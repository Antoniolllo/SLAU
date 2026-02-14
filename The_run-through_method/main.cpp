#include <iostream>
#include <vector>
#include "solver.hpp"

int main() {
    int n;

    std::cout << "input the number of elements in the middle diagonal: ";
    std::cin >> n;

    std::vector<double> a(n);
    std::vector<double> b(n);
    std::vector<double> c(n);
    std::vector<double> d(n);

    std::cout << "input lower diagonal (a):\n";
    for (int i = 1; i < n; i++) {
        std::cin >> a[i];
    }

    std::cout << "input middle diagonal (b):\n";
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }

    std::cout << "input upper diagonal (c):\n";
    for (int i = 0; i < n - 1; i++) {
        std::cin >> c[i];
    }

    std::cout << "input column d:\n";
    for (int i = 0; i < n; i++) {
        std::cin >> d[i];
    }

    std::vector<double> x = solver(a, b, c, d);

    std::cout << "solution x:\n";
    for (int i = 0; i < n; i++) {
        std::cout << x[i] << "\n";
    }

    return 0;
}

