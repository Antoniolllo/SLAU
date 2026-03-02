#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
class Vector {
private:
    std::vector<T> data;

public:

    	Vector(int size) {
		data.resize(size);
	}

	void fill() {
        	for (int i = 0; i < data.size(); ++i) {
        		std::cin >> data[i];
    		}
	}

	Vector<T> operator+(Vector<T>& other) {
        	if (data.size() != other.data.size()) {
            		throw std::invalid_argument("Vector sizes do not match");
        	}

        	Vector<T> result(data.size());

        	for (int i = 0; i < data.size(); ++i) {
            		result.data[i] = data[i] + other.data[i];
        	}

        	return result;

	}


	T operator*(Vector<T>& other) {
        	if (data.size() != other.data.size()) {
        		throw std::invalid_argument("Vector sizes do not match");
    		}

    		T result = T{};

    		for (int i = 0; i < data.size(); ++i) {
        		result += data[i] * other.data[i];
    		}

    		return result;
	}


	Vector<T> operator*(double n) {

    		Vector<T> result(data.size());

    		for (size_t i = 0; i < data.size(); ++i) {
        		result[i] = data[i] * n;
    		}

    		return result;
	}


	int size() const {
    		return data.size();
	}

	T& operator[](int i) {
    		return data[i];
	}

	const T& operator[](int i) const {
    		return data[i];
}

};
