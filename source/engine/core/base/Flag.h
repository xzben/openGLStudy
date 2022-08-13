#pragma once

#include "common.h"

BEGIN_OGS_NAMESPACE

template<typename T>
class Flag
{
public:
	void checkFlag(const int type)
	{
		ASSERT(type >= 0 && type < s_maxlen, "type must in range %d - %d", 0, s_maxlen);

		unsigned char* pbyte = &m_value;
		int index = type / 8;
		int flag = type % 8;

		pbyte[index] |= (1 << flag);
	}

	bool isCheck(const int type)
	{
		ASSERT(type >= 0 && type < s_maxlen, "type must in range %d - %d", 0, s_maxlen);

		unsigned char* pbyte = &m_value;
		int index = type / 8;
		int flag = type % 8;

		unsigned char checkflag = 1 << flag;

		return pbyte[index] & checkflag == checkflag;
	}

	bool operator==(const Flag<T>& other)
	{
		int count = s_maxlen / 8;
		unsigned char* pbyte1 = &m_value;
		unsigned char* pbyte2 = &other.m_value;

		for (int i = 0; i < count; i++)
		{
			if (pbyte1[i] != pbyte2[i])
			{
				return false;
			}
		}

		return true;
	}

	bool operator!=(const Flag<T>& other)
	{
		return !this->operator==(other);
	}

protected:
	static const int s_maxlen = sizeof(T);
	T m_value = 0;
};

typedef struct 
{
	unsigned char data[16];
}Flag128Data;

using Flag8 = Flag<char>;
using Flag16 = Flag<short>;
using Flag32 = Flag<int>;
using Flag64 = Flag<long long>;
using Flag128 = Flag<Flag128Data>;

END_OGS_NAMESPACE