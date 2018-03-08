#pragma once
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>



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
	Tree& insert(const val_type&);//Insert new node into tree
	Tree& remove(const val_type&);//Remove node from tree
	bool contain(const val_type& val) const;//find node in tree

	template <typename con = std::vector<val_type>>
	con inorder_print() const;

	template <typename con = std::vector<val_type>>
	con preorder_print() const;

	template <typename con = std::vector<val_type>>
	con postorder_print() const;

	template <typename val_type, typename comp_type = std::less<val_type>>
	friend std::ostream& operator<<(std::ostream&, const Tree<val_type, comp_type>&);

	~Tree()
	{
		destroy_tree(root);
	}
#define DEBUGMODE
#ifdef DEBUGMODE
	bool is_balanced()
	{
		return is_bal(root);
	}
	bool is_bal(Node* n)
	{
		bool res = true;
		res = balance_factor(n) <= 1 && balance_factor(n) >= -1;
		if(n->left!=nullptr)
		{
			res = res && is_bal(n->left);
		}
		if(n->right!=nullptr)
		{
			res = res && is_bal(n->right);
		}
		return res;
	}
#endif
private:
	comp_type pred;
	Node* root = nullptr;

	size_t height(Node*) const;//Returns height of tree with root in node. 0 if nullptr
	void reset_height(Node*);//Resets height of node based on height of child nodes
	int balance_factor(Node*);
	Node* rotate_left(Node*);
	Node* rotate_right(Node*);
	Node* balance(Node*);
	Node* insert(Node*, const val_type&);
	Node* remove(Node*, const val_type&);
	Node* find_max(Node*);
	Node* remove_max(Node*);
	Node* find(Node*, const val_type&) const;

	template <typename con>
	void inorder_print(con&, Node*) const;

	template <typename con>
	void postorder_print(con&, Node*) const;

	template <typename con>
	void preorder_print(con&, Node*) const;

	void print(std::ostream&, const Node*, int = 0) const;
	void destroy_tree(Node*);
};

template <typename val_type, typename comp_type>
bool Tree<val_type, comp_type>::contain(const val_type& val) const
{
	return find(root, val)!=nullptr;
}

template <typename val_type, typename comp_type>
template <typename con>
con Tree<val_type, comp_type>::inorder_print() const
{
	con result;
	inorder_print<con>(result, root);
	return std::move(result);
}

template <typename val_type, typename comp_type>
template <typename con>
con Tree<val_type, comp_type>::preorder_print() const
{
	con result;
	preorder_print<con>(result, root);
	return std::move(result);
}

template <typename val_type, typename comp_type>
template <typename con>
con Tree<val_type, comp_type>::postorder_print() const
{
	con result;
	postorder_print<con>(result, root);
	return std::move(result);
}

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
	/*
	 *	   1			         4
	 *	  / \                   / \
	 *	 2   4       --->      1   5
	 *	    / \			      / \   \
	 *	   3   5             2   3   6
	 *	        \ 
	 *	         6
	 */

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
	/*
	*	     4			          2
	*	    / \                  / \           
	*	   2   5    --->        1   4
	*	  / \ 			       /   / \
	*    1   3                0   3   5
	*	/       
	*  0         
	*/

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
			/*  
			 *   remove 6;          max in left subtree is 3
			 *                      6                       3
			 *                    /   \                   /   \
			 *                   2     12                2     12
			 *                  / \   /  \              /|    /  \   
			 *                 1   3 9    15           1 2   9    15 
			 *                    /
			 *                   2                         
			 */

			Node* max = find_max(rt->left);  //Find max element in left subtree 
			max->left = remove_max(rt->left); //Remove max element from left subtree, but save it's left child if exists
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
template <typename con>
void Tree<val_type, comp_type>::inorder_print(con& arr, Node* rt) const
{
	if(rt != nullptr)
	{
		inorder_print(arr, rt->left);
		arr.push_back(rt->key);
		inorder_print(arr, rt->right);
	}
}

template <typename val_type, typename comp_type>
template <typename con>
void Tree<val_type, comp_type>::postorder_print(con& arr, Node* rt) const
{
	if(rt != nullptr)
	{
		postorder_print(arr, rt->left);
		postorder_print(arr, rt->right);
		arr.push_back(rt->key);
	}
}

template <typename val_type, typename comp_type>
template <typename con>
void Tree<val_type, comp_type>::preorder_print(con& arr, Node* rt) const
{
	if(rt != nullptr)
	{
		arr.push_back(rt->key);
		preorder_print(arr, rt->left);
		preorder_print(arr, rt->right);
	}
}

template <typename val_type, typename comp_type>
void Tree<val_type, comp_type>::print(std::ostream& os, const Node* rt, int space) const
{
	while(rt != nullptr)
	{
		print(os, rt->right, space + 5);
		for(int i = 0; i < space; ++i)
		{
			os << " ";
		}
		os << rt->key << "\n";
		rt = rt->left;
		space += 5;
	}
}

template <typename val_type, typename comp_type>
void Tree<val_type, comp_type>::destroy_tree(Node* rt)
{
	if(rt != nullptr)
	{
		destroy_tree(rt->left);
		destroy_tree(rt->right);
		delete rt;
	}
}

