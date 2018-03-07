#include "Tree.h"
<<<<<<< HEAD
#include "gtest/gtest.h"
=======
#include <string>
#include <map>
using namespace std;

>>>>>>> master

using namespace std;

struct Tree_test: testing::Test
{
<<<<<<< HEAD
	Tree<int> tr;
};

TEST_P(Tree_test, insert_test)
{
	EXPECT_EQ(0, 0);
}
=======
	map<string, string> tr;
	tr["a"]="a";
	tr["b"] = "b";
	tr["c"] = "c";
	tr["d"] = "d";
	tr["f"] = "f";
	tr["m"] = "m";
	tr["h"] = "h";
	tr["o"] = "o";
	tr["p"] = "p";
	tr["q"] = "q";
	tr["e"] = "e";
	
	for(auto it=tr.begin(); it!=tr.end(); ++it)
	{
		cout << it->first << endl;
	}
>>>>>>> master

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}