#pragma once

#include "LinkedList.h"

template<typename T>
class ListQueue
{
public:
	// Pushes an item to the back of the queue
	void enqueue(T value)
	{
		_list.push_back(value);
	}

	// Pops an item from the front of the queue and returns its value
	T dequeue()
	{
		return _list.pop_front();
	}

	// Returns value of the item at the front of the queue
	T front()
	{
		return _list.front();
	}

	// Returns item count in the queue
	size_t size()
	{
		return _list.size();
	}

	// Returns true if queue is empty
	bool empty()
	{
		return _list.size() == 0;
	}


private:
	LinkedList<T> _list;
};