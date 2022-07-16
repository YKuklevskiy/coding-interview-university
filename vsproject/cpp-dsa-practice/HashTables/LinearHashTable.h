#pragma once
#include <cmath>
#include <exception>
#include <iostream>
#include "HashFunctions.h"	

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
		return HashFunctions::hash1<K>(key, _tableSize);
	}

	void insert(K key, V value) 
	{
		// if key entry already in table change it, otherwise insert new
		size_t itemIndex = findIndex(key);
		if (itemIndex != -1)
		{
			_table[itemIndex].value = value;
			return;
		}
			
		// didn't find existing entry, insert new one
		// TODO calls findEmpty entry which probes all the way to the end of cluster just as findIndex, inefficient
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
		size_t hashValue = hash(key);

		while (_table[hashValue].emptyFlag == 0)
		{
			hashValue = ++hashValue % _tableSize;
		}

		return hashValue;
	}

	// returns index of entry with the same key
	size_t findIndex(K key)
	{
		size_t hashValue = hash(key);

		while (_table[hashValue].emptyFlag != 1)
		{
			if (_table[hashValue].key == key && _table[hashValue].emptyFlag == 0)
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