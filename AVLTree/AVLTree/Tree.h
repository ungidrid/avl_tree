#pragma once
#include <iostream>
#include <functional>
#include <algorithm>


template <typename val_type, typename comp_type=std::less<val_type>>
class Tree
{
private:
	class Node
	{
	public:
		const val_type key;
		friend class Tree<val_type, comp_type>;
	private:
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
	Tree& insert(const val_type&);
	Tree& remove(const val_type&);
	Node* find(const val_type& val)const
	{
		return find(root, val);
	}

	template <typename val_type, typename comp_type = std::less<val_type>>
	friend std::ostream& operator<<(std::ostream&, const Tree<val_type, comp_type>&);

private:
	comp_type pred;
	Node* root = nullptr;

	size_t height(Node*) const;
	void reset_height(Node*);
	int balance_factor(Node*);
	Node* rotate_left(Node*);
	Node* rotate_right(Node*);
	Node* balance(Node*);
	Node* insert(Node*, const val_type&);
	Node* remove(Node*, const val_type&);
	Node* find_max(Node*);
	Node* remove_max(Node*);
	Node* find(Node*, const val_type&) const;

	void print(std::ostream&, const Node*, int = 0) const;
};

template <typename val_type, typename comp_type>
std::ostream& operator<<(std::ostream& os, const Tree<val_type, comp_type>& tr)
{
	tr.print(os, tr.root);
	return os;
}

template <typename val_type, typename comp_type>
Tree<val_type, comp_type>& Tree<val_type, comp_type>::insert(const val_type& val)
{
	root = insert(root, val);
	return *this;
}

template <typename val_type, typename comp_type>
Tree<val_type, comp_type>& Tree<val_type, comp_type>::remove(const val_type& val)
{
	root = remove(root, val);
	return *this;
}

template <typename val_type, typename comp_type>
size_t Tree<val_type, comp_type>::height(Node* rt) const
{
	return rt != nullptr ? rt->height : 0;
}

template <typename val_type, typename comp_type>
void Tree<val_type, comp_type>::reset_height(Node* rt)
{
	rt->height = std::max(height(rt->left), height(rt->right)) + 1;
}

template <typename val_type, typename comp_type>
int Tree<val_type, comp_type>::balance_factor(Node* rt)
{
	return height(rt->right) - height(rt->left);
}

template <typename val_type, typename comp_type>
typename Tree<val_type, comp_type>::Node* Tree<val_type, comp_type>::rotate_left(Node* rt)
{
	Node* new_rt = rt->right;
	rt->right = new_rt->left;
	new_rt->left = rt;
	reset_height(rt);
	reset_height(new_rt);
	return new_rt;
}

template <typename val_type, typename comp_type>
typename Tree<val_type, comp_type>::Node* Tree<val_type, comp_type>::rotate_right(Node* rt)
{
	Node* new_rt = rt->left;
	rt->left = new_rt->right;
	new_rt->right = rt;
	reset_height(rt);
	reset_height(new_rt);
	return new_rt;
}

template <typename val_type, typename comp_type>
typename Tree<val_type, comp_type>::Node* Tree<val_type, comp_type>::balance(Node* rt)
{
	reset_height(rt);
	if(balance_factor(rt) == 2)
	{
		if(balance_factor(rt->right) < 0)
		{
			rt->right = rotate_right(rt->right);
		}
		return rotate_left(rt);
	}
	if(balance_factor(rt) == -2)
	{
		if(balance_factor(rt->left) > 0)
		{
			rt->left = rotate_left(rt->left);
		}
		return rotate_right(rt);
	}
	return rt;
}

template <typename val_type, typename comp_type>
typename Tree<val_type, comp_type>::Node* Tree<val_type, comp_type>::insert(Node* rt, const val_type& val)
{
	if(rt == nullptr)
	{
		return new Node(val);
	}
	if(pred(val, rt->key))
	{
		rt->left = insert(rt->left, val);
	}
	else
	{
		rt->right = insert(rt->right, val);
	}
	return balance(rt);
}

template <typename val_type, typename comp_type>
typename Tree<val_type, comp_type>::Node* Tree<val_type, comp_type>::remove(Node* rt, const val_type& val)
{
	if(rt == nullptr)
	{
		return nullptr;
	}
	if(pred(val, rt->key))
	{
		//goto left subtree
		rt->left = remove(rt->left, val);
	}
	else
	{
		if(pred(rt->key, val))
		{
			//goto right subtree
			rt->right = remove(rt->right, val);
		}
		else
		{
			//key==val
			if(rt->left == nullptr)
			{
				return rt->right;
			}
			Node* max = find_max(rt->left);
			max->left = remove_max(rt->left);
			max->right = rt->right;
			delete rt;
			return balance(max);
		}
	}
	return balance(rt);
}

template <typename val_type, typename comp_type>
typename Tree<val_type, comp_type>::Node* Tree<val_type, comp_type>::find_max(Node* rt)
{
	return rt->right == nullptr ? rt : find_max(rt->right);
}

template <typename val_type, typename comp_type>
typename Tree<val_type, comp_type>::Node* Tree<val_type, comp_type>::remove_max(Node* rt)
{
	if(rt->right == nullptr)
	{
		return rt->left;
	}
	rt->right = remove_max(rt->right);
	return balance(rt);
}

template <typename val_type, typename comp_type>
typename Tree<val_type, comp_type>::Node* Tree<val_type, comp_type>::find(Node* rt, const val_type& val) const
{
	if(rt != nullptr)
	{
		if(pred(val, rt->key))
		{
			return find(rt->left, val);
		}
		if(pred(rt->key, val))
		{
			return find(rt->right, val);
		}
		return rt;
	}
	return nullptr;
}

template <typename val_type, typename comp_type>
void Tree<val_type, comp_type>::print(std::ostream& os, const Node* rt, int space) const
{
	while(rt != nullptr)
	{
		print(os, rt->right, space + 5);
		for(unsigned i = 0; i < space; ++i)
		{
			os << " ";
		}
		os << rt->key << "\n";
		rt = rt->left;
		space += 5;
	}
}

