all:
	g++ -std=c++17 tests/main.cpp src/mpi.cpp src/jacobi.cpp src/gauss_seidel.cpp -o main

run:
	./main

plot:
	python3 plot.py

clean:
	rm -f main *.csv *.png
