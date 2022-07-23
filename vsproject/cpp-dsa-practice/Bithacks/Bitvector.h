#pragma once
#include <iostream>
#include <cassert>

const int BITVECTOR_SIZE = 32;

class Bitvector
{
public:
	void set_bit(int position)
	{
		assert(position >= 0 && position < BITVECTOR_SIZE);

		unsigned int mask = 1 << position;
		_bitvector = _bitvector | mask;
	}

	void clear_bit(int position)
	{
		assert(position >= 0 && position < BITVECTOR_SIZE);

		unsigned int mask = 1 << position;
		_bitvector = _bitvector & (~mask);
	}

	void flip_bit(int position)
	{
		assert(position >= 0 && position < BITVECTOR_SIZE);

		unsigned int mask = 1 << position;
		_bitvector = _bitvector ^ mask;
	}

	// sets bit to state
	void modify_bit(int position, bool state)
	{
		assert(position >= 0 && position < BITVECTOR_SIZE);

		unsigned int mask = 1 << position;
		_bitvector = _bitvector & (~mask) | (state << position);
	}

	bool get_bit(int position)
	{
		assert(position >= 0 && position < BITVECTOR_SIZE);

		return ((_bitvector >> position) & 1) == 1;
	}

	unsigned int count_bits()
	{
		unsigned int temp = _bitvector;

		// as our bitvector is 32 bits we need 5 masks and 5 iterations only
		unsigned int masks[] =
		{
			0x55555555, // 01010101 01010101 01010101 01010101
			0x33333333, // 00110011 00110011 00110011 00110011
			0x0f0f0f0f, // 00001111 00001111 00001111 00001111
			0x00ff00ff, // 00000000 11111111 00000000 11111111
			0x0000ffff, // 00000000 00000000 11111111 11111111
		};

		int shift = 1;

		for (int i = 0; i < sizeof(masks) / sizeof(temp); i++)
		{
			unsigned int masked1 = temp & masks[i];
			unsigned int masked2 = (temp >> shift) & masks[i];
			temp = masked1 + masked2;

			shift <<= 1;
		}

		return temp;
	}

	int count_different_bits(Bitvector target) 
	{
		unsigned int temp = _bitvector;

		_bitvector = _bitvector ^ target._bitvector;
		int result = count_bits();

		_bitvector = temp;
		return result;
	}

	int get_length()
	{
		return sizeof(_bitvector) * 8;
	}

private:
	unsigned int _bitvector = 0;
};