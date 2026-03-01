#include <gtest/gtest.h>
#include "dense_matrix.hpp"

TEST(DenseMatrix, Sizes) {
    dense_matrix<int> A(3,4);
    EXPECT_EQ(A.get_size_rows(), 3);
    EXPECT_EQ(A.get_size_cols(), 4);
}

TEST(DenseMatrix, WriteRead) {
    dense_matrix<int> A(2,3);
    A.write(1,2,7);
    EXPECT_EQ(A.read(1,2), 7);
}

TEST(DenseMatrix, OutOfRangeRead) {
    dense_matrix<int> A(3,4);
    EXPECT_THROW(A.read(3,0), std::out_of_range);
}

TEST(DenseMatrix, OutOfRangeWrite) {
    dense_matrix<int> A(3,4);
    EXPECT_THROW(A.write(0,4,1), std::out_of_range);
}
