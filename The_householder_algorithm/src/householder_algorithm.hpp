#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>

template<typename T>
class dense_matrix_householder{

private:
        int size_cols;
        int size_rows;
        std::vector<T> data;

public:
        dense_matrix_householder(int rows, int cols) {
                size_rows = rows;
                size_cols = cols;
                data.resize(rows * cols);
        }

        int get_size_cols(){
                return size_cols;
        }

        int get_size_rows(){
                return size_rows;
        }

        void fill() {
                for (int i = 0; i < size_rows; ++i) {
                        for (int j = 0; j < size_cols; ++j) {
                                std::cin >> data[i * size_cols + j];
                        }
                }
        }

        T get(int i, int j) {
                return data[i * size_cols + j];
        }

	T& set(int i, int j) {
        	return data[i * size_cols + j];
	}

        void print() {
                for (int i = 0; i < size_rows; ++i) {
                        for (int j = 0; j < size_cols; ++j) {
                                std::cout << data[i * size_cols + j] << " ";
                        }
                        std::cout << "\n";
                }
        }

        dense_matrix_householder<T> multiply(dense_matrix_householder<T> other) {
                if (size_cols != other.size_rows) {
                        throw std::runtime_error("wrong sizes");
                }

                dense_matrix_householder<T> result(size_rows, other.size_cols);

                for (int i = 0; i < size_rows; ++i) {
                        for (int j = 0; j < other.size_cols; ++j) {
                                result.set(i, j) = 0;
                                for (int k = 0; k < size_cols; ++k) {
                                        result.set(i, j) += get(i, k) * other.get(k, j);
                                }
                        }
                }

                return result;
        }

        dense_matrix_householder<T> identity(int n) {
                dense_matrix_householder<T> E(n, n);

                for (int i = 0; i < n; ++i) {
                        for (int j = 0; j < n; ++j) {
                                if (i == j) {
                                        E.set(i, j) = 1;
                                } else {
                                        E.set(i, j) = 0;
                                }
                        }
                }

                return E;
        }

        void martix_QR(dense_matrix_householder<T>& Q, dense_matrix_householder<T>& R) {
                std::vector<T> x;

                Q = identity(size_rows);
                R = *this;

                for (int k = 0; k < size_cols && k < size_rows; ++k) {
                        x.resize(size_rows - k);

                        for (int i = k; i < size_rows; ++i) {
                                x[i - k] = R.get(i, k);
			}
                        T sum = 0;
                        for (int q = 0; q < x.size(); ++q) {
                                sum += x[q] * x[q];
                        }
                        T norm_x = std::sqrt(sum);

                        if (norm_x == 0) {
                                continue;
                        }

                        T alpha;
                        if (x[0] >= 0) {
                                alpha = -norm_x;
                        } else {
                                alpha = norm_x;
                        }

                   
                        std::vector<T> v = x;
                        v[0] -= alpha;



                        T vTv = 0;
                        for (int i = 0; i < v.size(); ++i) {
                                vTv += v[i] * v[i];
                        }

                        if (vTv == 0) {
                                continue;
                        }

                        dense_matrix_householder<T> P(v.size(), v.size());

                        for (int i = 0; i < v.size(); ++i) {
                                for (int j = 0; j < v.size(); ++j) {
                                        P.set(i, j) = -2 * v[i] * v[j] / vTv;
                                        if (i == j) {
                                                P.set(i, j) += 1;
                                        }
                                }
                        }

                        dense_matrix_householder<T> H = identity(size_rows);

                        for (int i = k; i < size_rows; ++i) {
                                for (int j = k; j < size_rows; ++j) {
                                        H.set(i, j) = P.get(i - k, j - k);
                                }
                        }

                        R = H.multiply(R);
                        Q = Q.multiply(H);
                }
        }
};
