#pragma once

/*




*/

template<typename K, typename V>
class IHashTable
{
public:
	virtual size_t hash(K key) = 0;
	virtual void insert(K key, V value) = 0;
	virtual void exists(K key) = 0;
	virtual V search(K key) = 0;
	virtual void remove(K key) = 0;

protected:
	virtual size_t hash_integral(K key) = 0;

	// Not O(1) if type is iterable like string, but its neat to be able to use strings as keys
	virtual size_t hash_nonintegral(K key) = 0;
};