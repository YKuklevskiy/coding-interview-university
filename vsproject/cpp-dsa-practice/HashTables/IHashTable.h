#pragma once

template<typename K, typename V>
class IHashTable
{
public:
	virtual size_t hash(K key) = 0;
	virtual void insert(K key, V value) = 0;
	virtual void exists(K key) = 0;
	virtual V search(K key) = 0;
	virtual void remove(K key) = 0;
};