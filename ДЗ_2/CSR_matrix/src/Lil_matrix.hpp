#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>

template<typename T>
class LIL_matrix {
private:
	int num_of_rows;
	int num_of_cols;
	std::vector<std::vector<std::pair<int, T>>> data;

public:
	LIL_matrix(int rows, int cols){
		num_of_rows = rows;
		num_of_cols = cols;
		data.resize(rows);

	}
        
	void add(int i, int j, const T& value) {
		if (i < 0 || i >= num_of_rows || j < 0 || j >= num_of_cols) {
        		throw std::out_of_range("Index out of range");
    		}

 		if (value == T{}) {
        		return;
    		}

		for (auto& element : data[i]) {
        		if (element.first == j){
            			element.second = value;
            			return;
        		}
    		}

		data[i].push_back({j, value});
	}


	int get_size_cols(){
        	return num_of_cols;
        }


        int get_size_rows(){
                return num_of_rows;
        }


	void print() {
    		for (int i = 0; i < num_of_rows; ++i) {
        		for (int j = 0; j < num_of_cols; ++j) {
            			T value = T{};
            				for ( auto& element : data[i]) {
                				if (element.first == j) {
                    					value = element.second;
                    					break;
                				}
            				}

            			std::cout << value << " ";
        		}
        	std::cout << "\n";
    		}
	}






};
