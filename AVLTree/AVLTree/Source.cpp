#include "Tree.h"
#include "gtest/gtest.h"

using namespace std;

struct Tree_test: testing::Test
{
	Tree<int> tr;
};

TEST_P(Tree_test, insert_test)
{
	EXPECT_EQ(0, 0);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}