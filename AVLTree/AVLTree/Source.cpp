#include <iostream>
#include "Tree.h"
#include <string>
using namespace std;



int main()
{
	Tree<string> tr;
	tr.insert("a");
	tr.insert("b");
	tr.insert("c");
	tr.insert("d");
	tr.insert("e");
	tr.insert("f");
	tr.insert("m");
	tr.insert("h");
	tr.insert("o");
	tr.insert("p");
	tr.insert("q");
	cout << tr << endl;

	auto con = tr.postorder_print();
	for (const auto& it : con)
		cout << it << endl;

}