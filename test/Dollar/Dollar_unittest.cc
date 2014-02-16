#include "gtest/gtest.h"
#include "Dollar/Dollar.h"

TEST(Dollar, testMultiplication){
	Dollar five(5);
	five.times(2);
	EXPECT_EQ(10, five.amount);
}
