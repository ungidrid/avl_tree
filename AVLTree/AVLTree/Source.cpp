#include <iostream>
#include "Tree.h"
using namespace std;

void Print(Tree<int>::Node *Ptr, int totalSpace)
{
	while (Ptr != nullptr)
	{
		Print(Ptr->right, totalSpace + 5);

		for (int i = 1; i <= totalSpace; i++)
			cout << " ";

		cout << Ptr->key << "\n";

		Ptr = Ptr->left;
		totalSpace += 5;
	}
}

int main()
{
	Tree<int> tr;
	for(size_t i=1; i<=10; ++i)
	{
		tr.push(i);
	}
	tr.push(4);

	tr.erase(8);
	Print(tr.root, 0);
}