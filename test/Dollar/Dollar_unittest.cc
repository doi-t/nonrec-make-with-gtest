#include "gtest/gtest.h"
#include "Dollar/Dollar.h"

TEST(Dollar, testMultiplication){
	Dollar five = Dollar(5);
	Dollar product = five.times(2);
	EXPECT_EQ(Dollar(10), product);
	product = five.times(3);
	EXPECT_EQ(Dollar(15), product);
}

TEST(Dollar, testEquality){
	EXPECT_TRUE(Dollar(5).equals(Dollar(5)));
	EXPECT_FALSE(Dollar(5).equals(Dollar(6)));
}
