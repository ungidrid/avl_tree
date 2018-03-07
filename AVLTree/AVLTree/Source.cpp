#include <iostream>
#include "Tree.h"
using namespace std;



int main()
{
	Tree<int> tr;
	for(size_t i=1; i<=10; ++i)
	{
		tr.push(i);
	}
	tr.push(4);
	tr.push(2);
	
	cout << tr << endl;

	cout << endl;
	cout << endl;

	tr.erase(4);
	cout << tr << endl;
}