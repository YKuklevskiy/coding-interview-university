#pragma once

#include "ListNode.h"

template<typename T>
class LinkedList
{
public:
	LinkedList() { }
	LinkedList(T value)
	{
		init(value);
	}

	~LinkedList()
	{
		while (_head != NULL)
		{
			auto temp = _head;
			_head = _head->_next;
			delete temp;
		}
	}
	
	// Returns element count
	size_t size() 
	{
		return _size;
	}
	
	// Returns true if size is 0
	bool empty()
	{
		return _size == 0;
	}

	// Returns the node at given index
	T value_at(size_t index)
	{
		return (*this)[index];
	}

	// Adds an node to the beginning of the list
	void push_front(T value)
	{
		if (_size == 0)
		{
			init(value);
			return;
		}

		ListNode<T>* temp = new ListNode<T>(value);
		temp->_next = _head;
		_head = temp;

		_size++;
	}

	// Adds an node to the end of the list
	T pop_front()
	{
		assert(_size != 0);

		auto temp = _head;
		T value = temp->_value;
		_head = temp->_next;
		delete temp;
		_size--;

		return value;
	}

	// Adds an node to the end of the list
	void push_back(T value)
	{
		if (_size == 0)
		{
			init(value);
			return;
		}

		ListNode<T>* temp = new ListNode<T>(value);
		_tail->_next = temp;
		_tail = temp;

		_size++;
	}

	// Returns an node from the beginning of the list
	T front()
	{
		return _head->_value;
	}

	// Returns an node from the end of the list
	T back()
	{
		return _tail->_value;
	}

	// Inserts an node at index, so current node at that index is pointed to by new node
	void insert(size_t index, T value)
	{
		assert(index >= 0 && index <= _size);

		if (index == 0)
		{
			push_front(value);
			return;
		}

		if (index == _size)
		{
			push_back(value);
			return;
		}

		ListNode<T>* nextNode = _head;
		
		for(int i = 0; i < index - 1; i++)
			nextNode = nextNode->_next;

		ListNode<T>* temp = new ListNode<T>(value);
		temp->_next = nextNode->_next;
		nextNode->_next = temp;

		_size++;
	}

	// Deletes an node at index
	void erase(size_t index)
	{
		assert(index >= 0 && index < _size);

		if (index == 0)
		{
			pop_front();
			return;
		}

		ListNode<T>* prevNode = _head;
		ListNode<T>* curNode = prevNode->_next;

		for (int i = 1; i < index; i++)
		{
			prevNode = curNode;
			curNode = curNode->_next;
		}

		erase(curNode, prevNode);
	}

	// Reverses the list
	void reverse()
	{
		if (_size == 0) return;

		ListNode<T>* first = _head;
		ListNode<T>* second = first->_next;

		first->_next = _head;

		while (second != NULL)
		{
			ListNode<T>* third = second->_next;
			second->_next = first;
			
			first = second;
			second = third;
		}

		_head->_next = NULL;

		std::swap(_head, _tail);
	}

	// Removes the first node in a list with this value if found
	void remove_value(T value)
	{
		if (_head->_value == value)
		{
			pop_front();
			return;
		}

		ListNode<T>* prevNode = _head;
		ListNode<T>* curNode = prevNode->_next;

		while (curNode != NULL)
		{
			if (curNode->_value == value)
			{
				erase(curNode, prevNode);
				return;
			}

			prevNode = curNode;
			curNode = curNode->_next;
		}
	}

	// Returns the first node with this value, NULL if not found
	ListNode<T>* find(T value)
	{
		ListNode<T>* curNode = _head;

		while (curNode != NULL)
		{
			if (curNode->_value == value)
				return curNode;

			curNode = curNode->_next;
		}

		return NULL;
	}

	// Allows to access and change value of a node. O(n)
	T& operator[](const size_t index)
	{
		assert(index >= 0 && index < _size);

		ListNode<T>* curNode = _head;
		for (int i = 0; i < index; i++)
			curNode = curNode->_next;

		return curNode->_value;
	}

private:
	size_t _size;

	ListNode<T>* _head = NULL;
	ListNode<T>* _tail = NULL;

	void init(T value)
	{
		_head = new ListNode<int>(value);
		_tail = _head;

		_size++;
	}

	// Deletes node nodeToDelete, previousNode is provided for O(1) time complexity
	void erase(ListNode<T>* nodeToDelete, ListNode<T>* previousNode)
	{
		// safe measures
		if (nodeToDelete == _head)
		{
			pop_front();
			return;
		}

		previousNode->_next = nodeToDelete->_next;
		delete nodeToDelete;

		if (previousNode->_next == NULL)
			_tail = previousNode;

		_size--;
	}

	template<typename T>
	friend class LinkedList_Tester;
};