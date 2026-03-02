#include <gtest/gtest.h>
#include "operation.hpp"
#include "Multiplying_from_a_matrix_by_a_vector.hpp"

TEST(VectorTest, AdditionWorks) {
    Vector<int> a(3);
    Vector<int> b(3);

    a[0] = 1; a[1] = 2; a[2] = 3;
    b[0] = 4; b[1] = 5; b[2] = 6;

    Vector<int> c = a + b;

    EXPECT_EQ(c[0], 5);
    EXPECT_EQ(c[1], 7);
    EXPECT_EQ(c[2], 9);
}

TEST(MatrixTest, MatrixVectorMultiplicationWorks) {
    Matrix<int> A(2, 3);
    Vector<int> x(3);

    A(0,0) = 1; A(0,1) = 2; A(0,2) = 3;
    A(1,0) = 4; A(1,1) = 5; A(1,2) = 6;

    x[0] = 1;
    x[1] = 1;
    x[2] = 1;

    Vector<int> y = A * x;

    EXPECT_EQ(y[0], 6);
    EXPECT_EQ(y[1], 15);
}
