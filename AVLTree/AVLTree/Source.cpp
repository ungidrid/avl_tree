#include <iostream>
#include "Tree.h"
using namespace std;



int main()
{
	Tree<int> tr;
	for(size_t i=1; i<=10; ++i)
	{
		tr.insert(i);
	}
	tr.insert(4);
	tr.insert(2);
	
	tr.remove(3);
	cout << tr.find(4)->key << endl;
}