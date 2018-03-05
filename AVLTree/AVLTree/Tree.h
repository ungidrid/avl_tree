#pragma once
#include <functional>
#include <algorithm>

#define DEBUG


template <typename val_type, typename comp_type=std::less<val_type>>
class Tree
{
#ifndef DEBUG
private:
#else
public:
#endif

	struct Node
	{
		val_type key;
		size_t height = 1;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(const val_type& k)
			: key(k)
		{
		}
	};

public:
	Tree() = default;

	Tree& push(const val_type& val)
	{
		root = insert(root, val);
		return *this;
	}

	Tree& erase(const val_type& val)
	{
		root = remove(root, val);
		return *this;
	}

#ifndef DEBUG
private:
#else
public:
#endif
	comp_type pred;
	Node* root = nullptr;

	size_t height(Node* p) const
	{
		return p != nullptr ? p->height : 0;
	}

	void reset_height(Node* p)
	{
		p->height = std::max(height(p->left), height(p->right)) + 1;
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
		if(balance_factor(root) == 2)
		{
			if(balance_factor(root->right) < 0)
			{
				root->right = rotate_right(root->right);
			}
			return rotate_left(root);
		}
		if(balance_factor(root) == -2)
		{
			if(balance_factor(root->left) > 0)
			{
				root->left = rotate_left(root->left);
			}
			return rotate_right(root);
		}
		return root;
	}

	Node* insert(Node* root, const val_type& key)
	{
		if(root == nullptr)
		{
			return new Node(key);
		}
		if(pred(root->key, key))
		{
			root->right = insert(root->right, key);
		}
		else
		{
			root->left = insert(root->left, key);
		}
		return balance(root);
	}

	Node* find_min(Node* root)
	{
		return root->left ? find_min(root->left) : root;
	}

	Node* remove_min(Node* root)
	{
		if (root->left == nullptr)
		{
			return root->right;
		}
		root->left = remove_min(root->left);
		return balance(root);
	}

	Node* remove(Node* root, const val_type& k)
	{
		if(root == nullptr)
		{
			return nullptr;
		}
		if(pred(k, root->key))
		{
			root->left = remove(root->left, k);
		}
		else
		{
			if(pred(root->key, k))
			{
				root->right = remove(root->right, k);
			}
			else
			{
				Node* left = root->left;
				Node* right = root->right;
				delete root;
				if(right == nullptr)
				{
					return left;
				}
				Node* min = find_min(right);
				min->right = remove_min(right);
				min->left = left;
				return balance(min);
			}
		}
		return balance(root);
	}
};
