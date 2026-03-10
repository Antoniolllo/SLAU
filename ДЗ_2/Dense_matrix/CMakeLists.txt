cmake_minimum_required(VERSION 3.10)
project(Dense_matrix)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(third_party/googletest-main)

add_executable(tests_dense_matrix
    tests/test_dense_matrix.cpp
)

target_include_directories(tests_dense_matrix PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(tests_dense_matrix PRIVATE
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests_dense_matrix)
