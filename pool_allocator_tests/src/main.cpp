//todo: what's the "Test Adapter for Google Test"
#include "gtest/gtest.h"
#include "PoolAllocator.h"


TEST(PoolAllocCtorTest, Positive)
{
	PoolAllocator pA1(1, 4);
	PoolAllocator pA2(2, 4);
	PoolAllocator pA3(3, 4);
	PoolAllocator pA4(4, 4);

	PoolAllocator pA5(1, 8);
	PoolAllocator pA6(2, 8);
	PoolAllocator pA7(3, 8);
	PoolAllocator pA8(4, 8);

	EXPECT_NE(nullptr, pA1.Pool());
	EXPECT_NE(nullptr, pA2.Pool());
	EXPECT_NE(nullptr, pA3.Pool());
	EXPECT_NE(nullptr, pA4.Pool());

	EXPECT_NE(nullptr, pA5.Pool());
	EXPECT_NE(nullptr, pA6.Pool());
	EXPECT_NE(nullptr, pA7.Pool());
	EXPECT_NE(nullptr, pA8.Pool());


	EXPECT_NE(nullptr, pA1.Top());
	EXPECT_NE(nullptr, pA2.Top());
	EXPECT_NE(nullptr, pA3.Top());
	EXPECT_NE(nullptr, pA4.Top());

	EXPECT_NE(nullptr, pA5.Top());
	EXPECT_NE(nullptr, pA6.Top());
	EXPECT_NE(nullptr, pA7.Top());
	EXPECT_NE(nullptr, pA8.Top());
}


TEST(PoolAllocCtorTest, Negative)
{
	PoolAllocator pA1(-1, 4);
	PoolAllocator pA2(1, -4);
	PoolAllocator pA3(-1, -4);

	EXPECT_EQ(nullptr, pA1.Pool());
	EXPECT_EQ(nullptr, pA2.Pool());
	EXPECT_EQ(nullptr, pA3.Pool());

	EXPECT_EQ(nullptr, pA1.Top());
	EXPECT_EQ(nullptr, pA2.Top());
	EXPECT_EQ(nullptr, pA3.Top());
}


TEST(PoolAllocCtorTest, Zero)
{
	PoolAllocator pA1(0, 4);
	PoolAllocator pA2(1, 0);
	PoolAllocator pA3(0, 0);

	EXPECT_EQ(nullptr, pA1.Pool());
	EXPECT_EQ(nullptr, pA2.Pool());
	EXPECT_EQ(nullptr, pA3.Pool());

	EXPECT_EQ(nullptr, pA1.Top());
	EXPECT_EQ(nullptr, pA2.Top());
	EXPECT_EQ(nullptr, pA3.Top());
}


TEST(PoolAllocCtorTest, Large)
{
	//todo: this should be a bit more dynamic and check both values against our predetermined max pool memory size
	PoolAllocator pA1(0x11111112, 1);
	PoolAllocator pA2(1, 0x04444445);
	//PoolAllocator pA3(0, 0);

	EXPECT_EQ(nullptr, pA1.Pool());
	EXPECT_EQ(nullptr, pA2.Pool());
	//EXPECT_EQ(nullptr, pA3.Pool());

	EXPECT_EQ(nullptr, pA1.Top());
	EXPECT_EQ(nullptr, pA2.Top());
	//EXPECT_EQ(nullptr, pA3.Top());
}



int main(int argc, char** argv)
{
	//todo: when this repo is cloned, there's a hard-coded include dir to the google-test library. which is lame.
	//todo: there are some other hardcoded include dirs too
	//todo: why is this scoping the way that it is
	//todo: warnings
	//todo: template for telling visual studio how to organize my projects
	::testing::InitGoogleTest(&argc, argv);

	int result = RUN_ALL_TESTS();

	//todo: why can i do this
	//PoolAllocator poola();

	std::cout << "Press Enter to continue . . ." ;
	std::cin.get();
	return result;

}