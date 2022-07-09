#pragma once
#include <cassert>

template<typename T>
class MyVector
{
public:
	MyVector(const size_t size)
	{
		_arr = new T[_capacity];

		if (size > _capacity)
		{

			size_t needed_capacity = std::pow(2, std::ceil(std::log2(size)));
			resize(needed_capacity);

		}

		std::fill(_arr, _arr + size, 0);

		_size = size;
	}

	// Returns element count
	size_t size()
	{
		return _size;
	}

	// Returns number of items the array can currently hold
	size_t capacity()
	{
		return _capacity;
	}

	// Returns true if size is 0
	bool is_empty()
	{
		return _size == 0;
	}

	// Returns the item at given index
	T at(const size_t index)
	{
		assert(index >= 0 && index < _size);

		return _arr[index];
	}

	// Adds an item to the end of the array
	void push(const T item)
	{
		insert(_size, item);
	}

	// Inserts an item at index and shifts all elements with >= index to the right
	void insert(const size_t index, const T item)
	{
		assert(index >= 0 && index <= _size);

		if (_size == _capacity)
			resize(_capacity * 2);

		for (size_t i = _size; i >= index + 1; i--)
			_arr[i] = _arr[i - 1];
		_arr[index] = item;

		_size++;
	}

	// Adds an item to the beginning of the array
	void prepend(const T item)
	{
		insert(0, item);
	}

	// Removes an item from the end, returns its value
	T pop()
	{
		int elem = _arr[_size - 1];
		erase(_size - 1);
		return elem;
	}

	// Deletes item at index, shifts all elements with >= index to the left
	void erase(const size_t index)
	{
		assert(index >= 0 && index < _size);

		for (size_t i = index; i < _size - 1; i++)
			_arr[i] = _arr[i + 1];

		_size--;

		if (_size <= _capacity / 4)
			resize(_capacity / 2);
	}

	// Finds all items in the array and deletes them
	void remove(const T item)
	{
		for (size_t i = 0; i < _size; i++)
		{

			if (_arr[i] == item)
			{
				erase(i);
				i--;
			}

		}
	}

	// Returns the first index of item in array, if none found returns -1
	size_t find(const T item)
	{
		for (size_t i = 0; i < _size; i++)
		{

			if (_arr[i] == item)
				return i;

		}

		return -1;
	}

	T& operator[](const size_t index)
	{
		assert(index >= 0 && index < _size);

		return _arr[index];
	}

private:
	T* _arr;
	size_t _size = 0;
	size_t _capacity = 16;

	// Resizes the array (copies it to new one of size 'capacity', flushes the old array)
	void resize(size_t capacity)
	{
		std::cout << "Resizing...";

		assert(capacity >= 0);
		_capacity = capacity;

		T* temp = _arr;
		_arr = new T[_capacity];

		//copy to new array
		for (size_t i = 0; i < _size; i++)
			_arr[i] = temp[i];

		delete[] temp;
	}
};