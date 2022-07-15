#pragma once
#include <cmath>
#include <exception>
#include <iostream>

//
//	-------- from https://en.cppreference.com/w/cpp/types/void_t --------
//

// Variable template that checks if a type has begin() and end() member functions
template <typename, typename = void>
constexpr bool is_iterable{};

template <typename T>
constexpr bool is_iterable<
	T,
	std::void_t< decltype(std::declval<T>().begin()),
	decltype(std::declval<T>().end())
	>
> = true;

//
//	---------------------------------------------------------------------
//

//
//		TODO Move hash functions inside the LinearHashTable class (somehow)
//

// O(1) space - types
template<typename K, 
	std::enable_if_t<is_iterable<K>, bool> = true>
size_t hash(K key, size_t tableSize)
{
	const int hashConstant = 2777; // prime
	size_t hashValue = 0;
	for (auto iter = key.begin(); iter != key.end(); iter++)
	{
		size_t value = (size_t)*iter;
		hashValue = ((hashValue * hashConstant) % tableSize + value) % tableSize;
	}

	return hashValue;
}

// iterable types
template<typename K, 
	std::enable_if_t<!is_iterable<K>, bool> = true>
size_t hash(K key, size_t tableSize)
{
	const float hashConstant = (std::sqrt(5) - 1) / 2;
	size_t value = (size_t)key;
	size_t hashValue = std::floor(tableSize * std::fmod(value * hashConstant, 1.0f));

	return hashValue;
}

//
//		CLASSES
//

template<typename K, typename V>
struct LinearTableEntry
{
	char emptyFlag = 1; // 1 if empty, 0 if filled, -1 if up for deletion
	K key;
	V value;
};

template<typename K, typename V>
// Hash table with linear probing collision solving
class LinearHashTable
{
public:
	LinearHashTable(size_t initialSize)
	{
		_tableSize = initialSize;
		_table = new LinearTableEntry<K, V>[_tableSize];
	}

	void insert(K key, V value) 
	{
		size_t entryIndex = findEmptyEntry(key);
		_table[entryIndex].key = key;
		_table[entryIndex].value = value;
		_table[entryIndex].emptyFlag = 0;

		_entryCount++;
	}
	
	bool exists(K key) 
	{
		size_t itemIndex = findIndex(key);
		bool value = itemIndex != -1;
		return value;
	}
	
	V search(K key) 
	{
		size_t itemIndex = findIndex(key);
		if(itemIndex == -1)
			throw new std::exception("Item doesn't exist in table.");

		return _table[itemIndex].value;
	}
	
	void remove(K key) 
	{
		size_t itemIndex = findIndex(key);
		if (itemIndex == -1)
			return;
		
		_table[itemIndex].emptyFlag = -1;
		_entryCount--;
	}

protected:

	size_t findEmptyEntry(K key)
	{
		size_t hashValue = hash(key, _tableSize);

		while (_table[hashValue].emptyFlag == 0)
		{
			hashValue = ++hashValue % _tableSize;
		}

		return hashValue;
	}

	// returns index of entry with the same key
	size_t findIndex(K key)
	{
		size_t hashValue = hash(key, _tableSize);

		while (_table[hashValue].emptyFlag != 1)
		{
			if (_table[hashValue].key == key)
				return hashValue;

			hashValue = ++hashValue % _tableSize;
		}
		return -1;
	}

private:
	size_t _tableSize = 1;
	size_t _entryCount = 0;

	LinearTableEntry<K, V>* _table = NULL;
};