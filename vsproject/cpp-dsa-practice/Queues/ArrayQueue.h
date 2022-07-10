#pragma once

#include <cassert>

const size_t DEFAULT_QUEUE_SIZE = 100;

template<typename T>
class ArrayQueue
{
public:
	ArrayQueue(size_t capacity = DEFAULT_QUEUE_SIZE)
	{
		assert(capacity > 0);

		_capacity = capacity;
		_array = new T[_capacity];
	}
	~ArrayQueue() { delete[] _array; }

	// Pushes an item to the back of the queue
	void enqueue(T value)
	{
		assert(!full());

		_array[_writeIndex] = value;
		_writeIndex = (_writeIndex + 1) % _capacity;

		_size++;
	}

	// Pops an item from the front of the queue and returns its value
	T dequeue()
	{
		T value = front();
		_readIndex = (_readIndex + 1) % _capacity;
		_size--;

		return value;
	}

	// Returns value of the item at the front of the queue
	T front()
	{
		assert(_size != 0);

		return _array[_readIndex];
	}

	// Returns item count in the queue
	size_t size()
	{
		return _size;
	}

	// Returns true if queue is empty
	bool empty()
	{
		return _size == 0;
	}

	bool full()
	{
		return _writeIndex == (_readIndex - 1 + _capacity) % _capacity;
	}

private:
	size_t _size = 0;
	size_t _capacity = DEFAULT_QUEUE_SIZE;
	size_t _writeIndex = 0;
	size_t _readIndex = 0;

	T* _array;
};