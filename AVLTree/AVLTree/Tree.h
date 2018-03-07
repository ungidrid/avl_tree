#pragma once
#include <iostream>
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

		explicit Node(const val_type& k)
			: key(k)
		{
		}
	};

public:
	Tree() = default;
	Tree& push(const val_type& val);
	Tree& erase(const val_type& val);

	template <typename val_type, typename comp_type = std::less<val_type>>
	friend std::ostream& operator<<(std::ostream& os, const Tree<val_type, comp_type>& tr);

#ifndef DEBUG
private:
#else
public:
#endif
	comp_type pred;
	Node* root = nullptr;

	size_t height(Node* p) const;
	void reset_height(Node* p);
	int balance_factor(Node* p);
	Node* rotate_left(Node* root);
	Node* rotate_right(Node* root);
	Node* balance(Node* root);
	Node* insert(Node* root, const val_type& val);
	Node* remove(Node* root, const val_type& val);
	Node* find_max(Node* root);
	Node* remove_max(Node* root);
	void print(std::ostream& os, const Node* root, int space = 0) const;
};

template <typename val_type, typename comp_type>
std::ostream& operator<<(std::ostream& os, const Tree<val_type, comp_type>& tr)
{
	tr.print(os, tr.root);
	return os;
}

template <typename val_type, typename comp_type>
Tree<val_type, comp_type>& Tree<val_type, comp_type>::push(const val_type& val)
{
	root = insert(root, val);
	return *this;
}

template <typename val_type, typename comp_type>
Tree<val_type, comp_type>& Tree<val_type, comp_type>::erase(const val_type& val)
{
	root = remove(root, val);
	return *this;
}

template <typename val_type, typename comp_type>
size_t Tree<val_type, comp_type>::height(Node* p) const
{
	return p != nullptr ? p->height : 0;
}

template <typename val_type, typename comp_type>
void Tree<val_type, comp_type>::reset_height(Node* p)
{
	p->height = std::max(height(p->left), height(p->right)) + 1;
}

template <typename val_type, typename comp_type>
int Tree<val_type, comp_type>::balance_factor(Node* p)
{
	return height(p->right) - height(p->left);
}

template <typename val_type, typename comp_type>
typename Tree<val_type, comp_type>::Node* Tree<val_type, comp_type>::rotate_left(Node* root)
{
	Node* new_root = root->right;
	root->right = new_root->left;
	new_root->left = root;
	reset_height(root);
	reset_height(new_root);
	return new_root;
}

template <typename val_type, typename comp_type>
typename Tree<val_type, comp_type>::Node* Tree<val_type, comp_type>::rotate_right(Node* root)
{
	Node* new_root = root->left;
	root->left = new_root->right;
	new_root->right = root;
	reset_height(root);
	reset_height(new_root);
	return new_root;
}

template <typename val_type, typename comp_type>
typename Tree<val_type, comp_type>::Node* Tree<val_type, comp_type>::balance(Node* root)
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

template <typename val_type, typename comp_type>
typename Tree<val_type, comp_type>::Node* Tree<val_type, comp_type>::insert(Node* root, const val_type& val)
{
	if(root == nullptr)
	{
		return new Node(val);
	}
	if(pred(val, root->key))
	{
		root->left = insert(root->left, val);
	}
	else
	{
		root->right = insert(root->right, val);
	}
	return balance(root);
}

template <typename val_type, typename comp_type>
typename Tree<val_type, comp_type>::Node* Tree<val_type, comp_type>::remove(Node* root, const val_type& val)
{
	if(root == nullptr)
	{
		return nullptr;
	}
	if(pred(val, root->key))
	{
		//goto left subtree
		root->left = remove(root->left, val);
	}
	else
	{
		if(pred(root->key, val))
		{
			//goto right subtree
			root->right = remove(root->right, val);
		}
		else
		{
			//key==val
			if(root->left == nullptr)
			{
				return root->right;
			}
			Node* max = find_max(root->left);
			max->left = remove_max(root->left);
			max->right = root->right;
			delete root;
			return balance(max);
		}
	}
	return balance(root);
}

template <typename val_type, typename comp_type>
typename Tree<val_type, comp_type>::Node* Tree<val_type, comp_type>::find_max(Node* root)
{
	return root->right == nullptr ? root : find_max(root->right);
}

template <typename val_type, typename comp_type>
typename Tree<val_type, comp_type>::Node* Tree<val_type, comp_type>::remove_max(Node* root)
{
	if(root->right == nullptr)
	{
		return root->left;
	}
	root->right = remove_max(root->right);
	return balance(root);
}

template <typename val_type, typename comp_type>
void Tree<val_type, comp_type>::print(std::ostream& os, const Node* root, int space) const
{
	while(root != nullptr)
	{
		print(os, root->right, space + 5);
		for(int i = 0; i < space; ++i)
		{
			os << " ";
		}
		os << root->key << "\n";
		root = root->left;
		space += 5;
	}
}

