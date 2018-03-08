#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#include "Tree.h"
#include "gtest/gtest.h"
#include <random>
using namespace std;


struct Tree_test: testing::Test
{
	Tree<int> tr;

	template<typename Con>
	static bool is_Sorted(const Con& c)
	{
		bool res = true;
		for (auto it = begin(c); it != end(c) - 1;)
		{
			if (*it>*++it)
			{
				res = false;
				break;
			}
		}
		return res;
	}
};

TEST_F(Tree_test, insert_test) {
	const unsigned N = 1000;
	for(unsigned i=0; i<N; ++i)
	{
		tr.insert(rand() % 20 + 1);
	}
	auto vec = tr.inorder_print();
	ASSERT_EQ(true, is_Sorted(vec));
	ASSERT_EQ(true, tr.is_balanced());
}

TEST_F(Tree_test, contain_test)
{
	tr.insert(10);
	tr.insert(42);
	tr.insert(42);
	ASSERT_EQ(true, tr.contain(10));
	ASSERT_EQ(true, tr.contain(42));
	tr.remove(42);
	ASSERT_EQ(true, tr.contain(42));
	tr.remove(42);
	ASSERT_EQ(false, tr.contain(42));
	ASSERT_EQ(false, tr.contain(41));
}

TEST_F(Tree_test, remove_test)
{
	const unsigned N = 1000;
	for (unsigned i = 0; i<N; ++i)
	{
		tr.insert(rand() % 20 + 1);
	}
	ASSERT_EQ(true, tr.is_balanced());

	int to_remove = rand() % 20 + 1;
	for(unsigned i=0; i<N; ++i)
	{
		tr.remove(to_remove);
	}
	auto vec = tr.inorder_print();
	ASSERT_EQ(true, is_Sorted(vec));
	ASSERT_EQ(false, tr.contain(to_remove));

	ASSERT_EQ(true, tr.is_balanced());
}



int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}