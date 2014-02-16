#include "gtest/gtest.h"
#include "Dollar/Dollar.h"

TEST(Dollar, testMultiplication){
	Dollar five = Dollar(5);
	Dollar product = five.times(2);
	EXPECT_EQ(10, product.amount);
	product = five.times(3);
	EXPECT_EQ(15, product.amount);
}

TEST(Dollar, testEquality){
	EXPECT_TRUE(Dollar(5).equals(Dollar(5)));
}
