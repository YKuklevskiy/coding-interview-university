#pragma once
#include <type_traits>
#include <iostream>
#include <cassert>

#include "TreeNode.h"

template <typename T, typename Enable = void>
class BST;

// My implementation does not allow multiple objects with the same value, 
// if you insert already existing value in tree no additional nodes will be created
template<typename T>
class BST< T, std::enable_if_t<std::is_arithmetic_v<T>> >
{
public:
	BST() { }
	BST(T value)
	{
		insert(value);
	}
	~BST()
	{
		delete_tree();
	}

	// insert value into tree
	void insert(T value)
	{
		if (_root == NULL) // tree empty
		{
			_root = new TreeNode<T>(value);
			_nodeCount++;
			return;
		}

		insert(value, _root);
	}

	// get count of values stored
	size_t get_node_count()
	{
		return _nodeCount;
	}

	// prints the values in the tree, from min to max
	void print_sorted()
	{
		if (_root == NULL) // tree empty
		{
			std::cout << "Tree is empty\n";
			return;
		}

		print_sorted(_root);
		std::cout << "\n";
	}

	void delete_tree()
	{
		if (_root == NULL) // tree empty
			return;

		delete_tree(_root);
		_nodeCount = 0;
		_root = NULL;
	}

	// returns true if given value exists in the tree
	bool is_in_tree(T value)
	{
		return find_in_tree(value, _root) != NULL;
	}

	// returns the height in nodes (single node's height is 1)
	size_t get_height()
	{
		if (_root == NULL) // tree empty
			return 0;

		return get_height(_root);
	}

	// returns the minimum value stored in the tree
	T get_min() 
	{
		assert(_root != NULL);

		return get_min(_root)->value;
	}

	// returns the maximum value stored in the tree
	T get_max() 
	{
		assert(_root != NULL);

		return get_max(_root)->value;
	}

	// don't know what's it for, except for testing, but ok
	bool is_binary_search_tree()
	{
		if (_root == NULL) // tree empty
			return true;

		return is_binary_search_tree(_root);
	}

	void delete_value(T value)
	{
		if (_root == NULL) // tree empty
			return;

		delete_value(value, _root);
	}

	// returns next-highest value in tree after given value
	T get_successor(T value) 
	{
		assert(_root != NULL);

		auto successor = _get_successor(value);

		if(successor != NULL)
			return successor->value;
		
		return 0;
	}

private:
	TreeNode<T>* _root = NULL;
	size_t _nodeCount = 0;

	//
	//		Encapsulated functions for recursive operations on nodes
	//

	void insert(T& value, TreeNode<T>* node)
	{
		if (node->value == value) // do nothing if value already in tree
			return;

		if (value < node->value) // less, add to left branch
		{
			if (node->left == NULL)
			{
				node->left = new TreeNode<T>(value, node);
				_nodeCount++;
				return;
			}

			insert(value, node->left);
			return;
		}
		else // more, add to right branch
		{
			if (node->right == NULL)
			{
				node->right = new TreeNode<T>(value, node);
				_nodeCount++;
				return;
			}

			insert(value, node->right);
			return;
		}
	}
	
	// Have to do inorder traversal
	void print_sorted(TreeNode<T>* node)
	{
		if (node->left != NULL)
			print_sorted(node->left);

		std::cout << node->value << " ";

		if (node->right != NULL)
			print_sorted(node->right);
	}
	
	void delete_tree(TreeNode<T>* node)
	{
		if (node->left != NULL)
			delete_tree(node->left);

		if (node->right != NULL)
			delete_tree(node->right);

		delete node;
	}
	
	TreeNode<T>* find_in_tree(T & value, TreeNode<T>* node)
	{
		if (node == NULL)
			return NULL;

		if (node->value == value)
			return node;

		if (value < node->value)
			return is_in_tree(node->left);
		else
			return is_in_tree(node->right);
	}
	
	size_t get_height(TreeNode<T>* node)
	{
		size_t leftSize = 0, rightSize = 0;
		if (node->left != NULL)
			leftSize = get_height(node->left);
		if (node->right != NULL)
			rightSize = get_height(node->right);

		return 1 + std::max(leftSize, rightSize);
	}
	
	TreeNode<T>* get_min(TreeNode<T>* node)
	{
		if (node->left == NULL)
			return node;

		return get_min(node->left);
	}
	
	TreeNode<T>* get_max(TreeNode<T>* node)
	{
		if (node->right == NULL)
			return node;

		return get_max(node->right);
	}
	
	bool is_binary_search_tree(TreeNode<T>* node)
	{
		bool flag = true;

		if (node->left != NULL)
			flag = flag && is_binary_search_tree(node->left) && (node->value > node->left->value);
		if (node->right != NULL)
			flag = flag && is_binary_search_tree(node->right) && (node->value < node->right->value);

		return flag;
	}
	
	void delete_value(T& value, TreeNode<T>* node)
	{
		if (node == NULL)
			return;

		if (node->value == value)
		{
			delete_node(node);
			_nodeCount--;
			return;
		}

		if (value < node->value)
			delete_value(value, node->left);
		else
			delete_value(value, node->right);
	}

	enum NODE_TYPE
	{
		CHILDLESS = 0b00,
		LEFT_CHILD = 0b10,
		RIGHT_CHILD = 0b01,
		BOTH_CHILDREN = 0b11
	};

	void delete_node(TreeNode<T>* node)
	{
		NODE_TYPE type = CHILDLESS;

		if (node->left != NULL)
			type = (NODE_TYPE) (type | LEFT_CHILD);

		if (node->right != NULL)
			type = (NODE_TYPE) (type | RIGHT_CHILD);

		switch (type)
		{
		case CHILDLESS:
			delete_leaf_node(node);
			break;
		case LEFT_CHILD:
		case RIGHT_CHILD:
			delete_single_child_node(node, type);
			break;
		case BOTH_CHILDREN:
			delete_double_child_node(node);
			break;
		default:
			break;
		}
	}

#pragma region SpecifiedDeleteFunctions
	void delete_leaf_node(TreeNode<T>* node)
	{
		auto parent = node->parent;

		if (parent->left == node)
			parent->left = NULL;
		else
			parent->right = NULL;

		delete node;
	}

	void delete_single_child_node(TreeNode<T>* node, NODE_TYPE type)
	{
		auto parent = node->parent;
		TreeNode<T>* child;

		if (type == LEFT_CHILD)
			child = node->left;
		else
			child = node->right;

		child->parent = parent;

		if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;

		delete node;
	}

	void delete_double_child_node(TreeNode<T>* node)
	{
		auto successor = get_min(node->right);
		std::swap(node->value, successor->value);
		
		delete_node(successor); // successor is either a leaf or has one child
	}
#pragma endregion
	
	// this function is actually just finding next node in inorder traversal of the tree
	TreeNode<T>* _get_successor(T & value)
	{
		auto parent_node = get_parent_of_node_with_value(value, _root);

		// stage 1. cases where value is in the tree
		if (parent_node == NULL) // the successor can be only in the right subtree of BST
		{
			if (_root->right != NULL) // the successor is in right subtree of the root
				return get_min(_root->right);
		}

		auto leftNode = parent_node->left, rightNode = parent_node->right;
		if (leftNode != NULL && leftNode->value == value) // value in tree and is the left child of parent_node
		{
			if (leftNode->right != NULL) // the successor is in right subtree of leftNode
				return get_min(leftNode->right);

			return parent_node; // as the successor is not in the valuenode's subtree, it is the parent which is larger than valuenode
		}

		if (rightNode != NULL && rightNode->value == value) // value in tree and is the right child of parent_node
		{
			if (rightNode->right != NULL) // the successor is in right subtree of rightNode
				return get_min(rightNode->right);
		}

		// stage 2. value is not in the tree. 
		// we go up in tree until we find parent that is larger than value or reached root
		auto temp_node = parent_node;
		while (temp_node != NULL && temp_node->value <= value)
		{
			temp_node = temp_node->parent;
		}

		// we either found first node that is larger than value, 
		// or haven't found anything which means there are no successors.
		return temp_node;
	}

	TreeNode<T>* get_parent_of_node_with_value(T& value, TreeNode<T>* node)
	{
		if (node->value == value) // root node has this value
			return NULL;

		if (value < node->value) // less, search in left branch
		{
			if (node->left == NULL || node->left->value == value)
				return node;
			
			return get_parent_of_node_with_value(value, node->left);
		}
		else					 // more, search in right branch
		{
			if (node->right == NULL || node->right->value == value)
				return node;

			return get_parent_of_node_with_value(value, node->right);
		}
	}

	friend class BSTTester;
};