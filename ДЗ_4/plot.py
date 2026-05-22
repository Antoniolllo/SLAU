import csv
import matplotlib.pyplot as plt


def read_method_file(filename):
    iterations = []
    residuals = []
    times = []

    with open(filename, "r") as file:
        reader = csv.DictReader(file)

        for row in reader:
            iterations.append(int(row["iteration"]))
            residuals.append(float(row["residual"]))
            times.append(float(row["time_ms"]))

    return iterations, residuals, times


def read_comparison_file(filename):
    methods = []
    iterations = []
    times = []

    with open(filename, "r") as file:
        reader = csv.DictReader(file)

        for row in reader:
            methods.append(row["method"])
            iterations.append(int(row["iterations"]))
            times.append(float(row["time_ms"]))

    return methods, iterations, times


mpi_iter, mpi_res, mpi_time = read_method_file("mpi.csv")
jacobi_iter, jacobi_res, jacobi_time = read_method_file("jacobi.csv")
gs_iter, gs_res, gs_time = read_method_file("gauss_seidel.csv")

methods, method_iterations, method_times = read_comparison_file("comparison.csv")


plt.figure()
plt.plot(mpi_iter, mpi_res, label="MPI")
plt.plot(jacobi_iter, jacobi_res, label="Jacobi")
plt.plot(gs_iter, gs_res, label="Gauss-Seidel")
plt.yscale("log")
plt.xlabel("Iteration")
plt.ylabel("Residual norm")
plt.title("Convergence by iterations")
plt.grid(True)
plt.legend()
plt.savefig("convergence_iterations.png")


plt.figure()
plt.plot(mpi_time, mpi_res, label="MPI")
plt.plot(jacobi_time, jacobi_res, label="Jacobi")
plt.plot(gs_time, gs_res, label="Gauss-Seidel")
plt.yscale("log")
plt.xlabel("Time, ms")
plt.ylabel("Residual norm")
plt.title("Convergence by time")
plt.grid(True)
plt.legend()
plt.savefig("convergence_time.png")


plt.figure()
plt.bar(methods, method_iterations)
plt.xlabel("Method")
plt.ylabel("Iterations")
plt.title("Number of iterations")
plt.grid(True)
plt.savefig("iterations_comparison.png")


plt.figure()
plt.bar(methods, method_times)
plt.xlabel("Method")
plt.ylabel("Time, ms")
plt.title("Time comparison")
plt.grid(True)
plt.savefig("time_comparison.png")


print("Plots were saved:")
print("convergence_iterations.png")
print("convergence_time.png")
print("iterations_comparison.png")
print("time_comparison.png")
