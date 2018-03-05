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
	for(size_t i=0; i<20; ++i)
	{
		tr.push(i);
	}
	Print(tr.root, 0);

	tr.erase(2);

	Print(tr.root, 0);
}