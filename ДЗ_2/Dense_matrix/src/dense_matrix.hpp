#include <iostream>
#include <vector>
#include <stdexcept>



template<typename T>
class dense_matrix{

private:
        int size_cols;
        int size_rows;
        std::vector<T> data;

public:
        dense_matrix(int rows, int cols) {
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
                                data[i * size_cols + j] = i * size_cols + j + 1;
                        }
                }
        }

        T read(int i, int j) const {
                if (i < 0 || i >= size_rows || j < 0 || j >= size_cols) {
                        throw std::out_of_range("Index out of range");
                }

                return data[i * size_cols + j];
        }

	void write(int i, int j, T x){
                if (i < 0 || i >= size_rows || j < 0 || j >= size_cols) {
                        throw std::out_of_range("Index out of range");
                }

                data[i * size_cols + j] = x;

        }



};
