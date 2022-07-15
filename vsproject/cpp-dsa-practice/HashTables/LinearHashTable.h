#pragma once
#include <cmath>
#include <exception>
#include <iostream>

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

	size_t hash(K key)
	{
		size_t value = (size_t)key;
		size_t hashValue = std::floor(_tableSize * std::fmod(value * c, 1.0f));

		return hashValue;
	}

	void insert(K key, V value) 
	{
		_table[findEmptyEntry(key)].value = value;
		_table[findEmptyEntry(key)].key = key;
		_table[findEmptyEntry(key)].emptyFlag = 0;
	}
	
	bool exists(K key) 
	{
		size_t itemIndex = findIndex(key);
		bool value = itemIndex != SIZE_MAX;
		return value;
	}
	
	V search(K key) 
	{
		size_t itemIndex = findIndex(key);
		if(itemIndex == SIZE_MAX)
			throw new std::exception("Item doesn't exist in table.");

		return _table[itemIndex].value;
	}
	
	void remove(K key) 
	{
		size_t itemIndex = findIndex(key);
		if (itemIndex == SIZE_MAX)
			return;
		
		_table[itemIndex].emptyFlag = -1;
	}

protected:
	const float c = (std::sqrt(5) - 1) / 2;

	size_t findEmptyEntry(K key)
	{
		size_t hashValue = hash(key);
		while (_table[hashValue].emptyFlag == 0)
		{
			hashValue = ++hashValue % _tableSize;
		}
		return hashValue;
	}

	size_t findIndex(K key)
	{
		size_t hashValue = hash(key);

		while (_table[hashValue].emptyFlag != 1)
		{
			if (_table[hashValue].key == key)
				return hashValue;

			hashValue = ++hashValue % _tableSize;
		}
		return SIZE_MAX;
	}

	size_t hash_integral(K key);

	size_t hash_nonintegral(K key);

private:
	size_t _tableSize;
	size_t _entryCount;

	LinearTableEntry<K, V>* _table = NULL;
};