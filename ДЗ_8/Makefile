all:
	g++ -std=c++17 test/main.cpp src/jacobi.cpp src/gauss_seidel.cpp src/symmetric_gauss_seidel.cpp src/gmres.cpp -o main

run:
	./main

clean:
	rm -f main history.csv
