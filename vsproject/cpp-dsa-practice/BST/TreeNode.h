#pragma once
#include <type_traits>

template <typename T, typename Enable = void>
class TreeNode;

template<typename T>
struct TreeNode< T, std::enable_if_t<std::is_arithmetic_v<T>> >
{
	T value;
	TreeNode<T>* parent = NULL;
	TreeNode<T>* left = NULL;
	TreeNode<T>* right = NULL;

	TreeNode(T value)
	{ 
		this->value = value;
	}

	TreeNode(T value, TreeNode<T>* parent)
		: TreeNode(value) 
	{ 
		this->parent = parent;
	}
};