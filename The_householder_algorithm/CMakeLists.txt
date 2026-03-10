cmake_minimum_required(VERSION 3.10)

project(householder_solver)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(test_householder
        test/main.cpp
)
