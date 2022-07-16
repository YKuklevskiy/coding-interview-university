#pragma once
#include <type_traits>
#include <cmath>

namespace HashFunctions
{

#pragma region isIterDecl

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

#pragma endregion

	const float NON_CONTAINER_HASH_CONSTANT = (std::sqrt(5) - 1) / 2;
	const int CONTAINER_HASH_CONSTANT = 2777; // prime

	// iterable types
	template<typename K, 
		std::enable_if_t<is_iterable<K>, bool> = true>
	size_t hash1(K key, size_t tableSize) 
	{
		size_t hashValue = 0;
		for (auto iter = key.begin(); iter != key.end(); iter++)
		{
			size_t value = (size_t)*iter;
			hashValue = ((hashValue * CONTAINER_HASH_CONSTANT) % tableSize + value) % tableSize;
		}

		return hashValue;
	}

	// O(1) space - types
	template<typename K,
		std::enable_if_t<!is_iterable<K>, bool> = true>
	size_t hash1(K key, size_t tableSize)
	{
		size_t value = (size_t)key;
		size_t hashValue = std::floor(tableSize * std::fmod(value * NON_CONTAINER_HASH_CONSTANT, 1.0f));

		return hashValue;
	}
}