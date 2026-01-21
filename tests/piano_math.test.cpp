#include <gtest/gtest.h>
#include <engine/core/gtest_math.h>

TEST(AdditionTest, HandlesPositiveNumbers) {
    EXPECT_EQ(piano_add(2, 3), 5);
}

TEST(AdditionTest, HandlesNegativeNumbers) {
    EXPECT_EQ(piano_add(-1, -1), -2);
}