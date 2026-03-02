#include <vector>
#include <stdexcept>


template<typename T>
class Matrix {
private:
    int rows, cols;
    std::vector<std::vector<T>> data;

public:
	Matrix(int r, int c) {
		rows = r;
		cols = c;
		data.resize(r);
 		for (int i = 0; i < r; ++i) {
        		data[i].resize(c);
    		}
	}

    Vector<T> operator*(const Vector<T>& v) const {

        if (cols != v.size()) {
            throw std::invalid_argument("Matrix and vector sizes do not match");
        }

        Vector<T> result(rows);

        for (int i = 0; i < rows; ++i) {

            T sum = T{};

            for (int j = 0; j < cols; ++j) {
                sum += data[i][j] * v[j];
            }

            result[i] = sum;
        }

        return result;
    }

	T& operator()(int i, int j) {
    		return data[i][j];
	}

	const T& operator()(int i, int j) const {
    		return data[i][j];
	}



};
