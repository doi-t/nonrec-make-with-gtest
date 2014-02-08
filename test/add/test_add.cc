#include "gtest/gtest.h"
#include "add/add.h"

TEST(AddTest, SampleTest)
{
	EXPECT_EQ(add(1,1), 2);
	EXPECT_EQ(add(5,5), 10);
}
