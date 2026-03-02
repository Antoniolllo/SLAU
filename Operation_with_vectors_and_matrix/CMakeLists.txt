cmake_minimum_required(VERSION 3.14)
project(linear_tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(third_party/googletest-main)

add_executable(unit_tests
    tests/tests.cpp
)

target_include_directories(unit_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(unit_tests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)
