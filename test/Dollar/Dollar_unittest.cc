#include "gtest/gtest.h"
#include "Dollar/Dollar.h"

TEST(Dollar, testMultiplication){
	Dollar five = Dollar(5);
	EXPECT_EQ(Dollar(10), five.times(2));
	EXPECT_EQ(Dollar(15), five.times(3));
}

TEST(Dollar, testEquality){
	EXPECT_TRUE(Dollar(5) == Dollar(5));
	EXPECT_FALSE(Dollar(5) == (Dollar(6)));
}
