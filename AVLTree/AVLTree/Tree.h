#pragma once
#include <functional>

template<typename val_type, typename comp_type=std::less<val_type>>
class Tree
{
private:
	struct Node
	{
		val_type key;
		size_t height = 1;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(const val_type& k) :key(k){}
	};

public:

private:
	comp_type pred;
	Node* root;

};
