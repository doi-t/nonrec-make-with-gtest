#include "gtest/gtest.h"
#include "Dollar/Dollar.h"

TEST(Dollar, testMultiplication){
	Money money;
	Dollar five = money.dollar(5);
	EXPECT_EQ(Dollar(10), five.times(2));
	EXPECT_EQ(Dollar(15), five.times(3));
}

TEST(Dollar, testEquality){
	EXPECT_TRUE(Dollar(5) == Dollar(5));
	EXPECT_FALSE(Dollar(5) == Dollar(6));
	EXPECT_TRUE(Franc(5) == Franc(5));
	EXPECT_FALSE(Franc(5) == Franc(6));
	EXPECT_FALSE(Franc(5) == Dollar(5));
}

TEST(Dollar, testFrancMultiplication){
	Franc five = Franc(5);
	EXPECT_EQ(Franc(10), five.times(2));
	EXPECT_EQ(Franc(15), five.times(3));
}

