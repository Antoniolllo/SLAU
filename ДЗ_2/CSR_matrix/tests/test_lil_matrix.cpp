#include <gtest/gtest.h>
#include <stdexcept>

#include "LIL_matrix.hpp"

TEST(LILMatrix, Sizes) {
    LIL_matrix<int> A(3, 4);
    EXPECT_EQ(A.get_size_rows(), 3);
    EXPECT_EQ(A.get_size_cols(), 4);
}

TEST(LILMatrix, AddDoesNotThrowInRange) {
    LIL_matrix<int> A(2, 3);
    EXPECT_NO_THROW(A.add(0, 0, 5));
    EXPECT_NO_THROW(A.add(1, 2, 7));
}

TEST(LILMatrix, AddThrowsOutOfRange) {
    LIL_matrix<int> A(2, 3);
    EXPECT_THROW(A.add(2, 0, 1), std::out_of_range);
    EXPECT_THROW(A.add(0, 3, 1), std::out_of_range);
    EXPECT_THROW(A.add(-1, 0, 1), std::out_of_range);
    EXPECT_THROW(A.add(0, -1, 1), std::out_of_range);
}

TEST(LILMatrix, AddZeroIsIgnored) {
    LIL_matrix<int> A(2, 3);

    EXPECT_NO_THROW(A.add(0, 1, 0));

    SUCCEED();
}

