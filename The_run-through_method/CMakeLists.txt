cmake_minimum_required(VERSION 3.10)

project(The_run-through_method)

set(CMAKE_CXX_STANDARD 17)

add_executable(main
    main.cpp
    solver.cpp
    solver.hpp
)
