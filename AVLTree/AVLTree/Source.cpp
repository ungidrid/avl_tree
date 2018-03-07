#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include "Tree.h"
#include "gtest/gtest.h"
#include <string>
#include <map>
using namespace std;


using namespace std;

struct Tree_test: testing::Test
{
	Tree<int> tr;
};


	

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}