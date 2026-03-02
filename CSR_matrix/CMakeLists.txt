cmake_minimum_required(VERSION 3.10)
project(CSR_matrix CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(third_party/googletest-main)

add_executable(tests_CSR_matrix
    tests/test_lil_matrix.cpp
)

target_include_directories(tests_CSR_matrix PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(tests_CSR_matrix PRIVATE
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests_CSR_matrix)
