#pragma once

/*




*/

template<typename K, typename V>
class IHashTable
{
public:
	virtual void hash(K key) = 0;
	virtual void insert(K key, V value) = 0;
	virtual void exists(K key) = 0;
	virtual void search(K key) = 0;
	virtual void remove(K key) = 0;

protected:
	virtual void hash_integral(K key) = 0;

	// Not O(1) if type is iterable like string, but its neat to be able to use strings as keys
	virtual void hash_nonintegral(K key) = 0;
};