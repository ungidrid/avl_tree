#pragma once
#include <functional>
#include <algorithm>

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

	size_t height(Node* p)const
	{
		return p != nullptr ? p->height : 0;
	}
	void reset_height(Node* p)
	{
		p->height = std::max(p->left->height, p->right->height) + 1;
	}
	int balance_factor(Node* p)
	{
		return height(p->right) - height(p->left);
	}

	Node* rotate_left(Node* root)
	{
		Node* new_root = root->right;
		root->right = new_root->left;
		new_root->left = root;
		reset_height(root);
		reset_height(new_root);
		return new_root;
	}
	Node* rotate_right(Node* p)
	{
		Node* new_root = root->left;
		root->left = new_root->right;
		new_root->right = root;
		reset_height(root);
		reset_height(new_root);
		return new_root;
	}
	Node* balance(Node* root)
	{
		reset_height(root);
		if(balance_factor(root)==2)
		{
			if (balance_factor(root->right) < 0)
			{
				root->right = rotate_right(root->right);
			}
			return rotate_left(root);
		}
		if(balance_factor(root)==-2)
		{
			if(balance_factor(root->left)>0)
			{
				root->left = rotate_left(root->left);
			}
			return rotate_right(root);
		}
		return root;
	}
};
