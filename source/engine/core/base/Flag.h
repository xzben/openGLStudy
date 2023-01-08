#pragma once

#include "common.h"

BEGIN_OGS_NAMESPACE

template<int FLAG_SIZE>
class Flag
{
public:
	enum
	{
		MIN_SIZE = 8,
		BYTE_COUNT = (FLAG_SIZE + MIN_SIZE - 1) / MIN_SIZE,
	};

	Flag()
	{
		clear();
	}

	void setAll()
	{
		memset(m_value, 0xff, BYTE_COUNT);
	}

	void clear()
	{
		memset(m_value, 0, BYTE_COUNT);
	}

	void checkFlag(const int type)
	{
		ASSERT(type >= 0 && type < FLAG_SIZE, "type must in range %d - %d", 0, FLAG_SIZE);

		byte* pbyte = m_value;
		int index = type / MIN_SIZE;
		int flag = type % MIN_SIZE;

		pbyte[index] |= (1 << flag);
	}

	bool isOpen(const int type)
	{
		ASSERT(type >= 0 && type < FLAG_SIZE, "type must in range %d - %d", 0, FLAG_SIZE);

		byte* pbyte = m_value;
		int index = type / MIN_SIZE;
		int flag = type % MIN_SIZE;

		unsigned char checkflag = 1 << flag;

		return pbyte[index] & checkflag == checkflag;
	}

	bool operator==(const Flag<FLAG_SIZE>& other)
	{
		byte* pbyte1 = m_value;
		byte* pbyte2 = other.m_value;

		for (int i = 0; i < BYTE_COUNT; i++)
		{
			if (pbyte1[i] != pbyte2[i])
			{
				return false;
			}
		}

		return true;
	}

	bool operator!=(const Flag<FLAG_SIZE>& other)
	{
		return !this->operator==(other);
	}

protected:
	byte m_value[BYTE_COUNT];

};

using Flag8 = Flag<8>;
using Flag16 = Flag<16>;
using Flag32 = Flag<32>;
using Flag64 = Flag<64>;
using Flag128 = Flag<128>;

END_OGS_NAMESPACE