CXX = g++
FLAGS = -std=c++17 -Wall

all:
	$(CXX) $(FLAGS) tests/main.cpp src/mpi.cpp src/chebyshev.cpp src/jacobi.cpp src/gauss_seidel.cpp -o main

run: all
	./main

clean:
	rm -f main
