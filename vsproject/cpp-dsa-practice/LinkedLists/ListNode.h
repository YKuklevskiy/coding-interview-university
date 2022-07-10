#pragma once

#include <cassert>

template<typename T>
class ListNode
{
public:
	ListNode(T value)
		: _value(value) { }

	T getValue() const { return _value; }

private:
	T _value;
	ListNode* _next = NULL;

	template<typename T>
	friend class LinkedList;

	template<typename T>
	friend class LinkedList_Tester;
};