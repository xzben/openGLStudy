#include "Data.h"
#include <cstdio>
BEGIN_OGS_NAMESPACE


Data::Data()
{
	reverse(MIN_DATA_BUFF);
}

Data::~Data()
{
	SAFE_DELTE(m_data);
}

void Data::reverse(int size)
{
	if (size <= m_capacity) return;

	int oldsize = m_capacity;
	while (m_capacity < size) m_capacity *= 2;

	byte* newdata = (byte*)malloc(m_capacity);
	if (oldsize > 0 && m_data)
	{
		memset(newdata, 0, m_capacity);
		memcpy(newdata, m_data, oldsize);
	}
	m_data = newdata;
}

int  Data::readBuff(byte* dest, int size)
{
	int rsize = size;
	int remainSize = m_size - m_rIndex;
	if (rsize > remainSize)
	{
		rsize = remainSize;
	}

	memcpy(dest, m_data + m_rIndex, rsize);

	return rsize;
}

int Data::readOffset(int offet)
{
	if (m_rIndex + offet > m_size)
		offet = m_size - m_rIndex;

	m_rIndex += offet;

	return offet;
}

int  Data::writeBuff(byte* src, int size)
{
	int remainSize = m_capacity - m_size;
	
	if (size > remainSize) {
		int newCapcity = m_capacity;
		while (newCapcity - m_size < size) newCapcity *= 2;
		reverse(newCapcity);
	}

	memcpy(m_data + m_size, src, size);
	m_size += size;

	return m_size;
}

int Data::writeOffset(int offset)
{
	if (m_capacity - m_size < offset)
	{
		int newCapcity = m_capacity;
		while (newCapcity - m_size < offset) newCapcity *= 2;
		reverse(newCapcity);
	}

	m_size += offset;

	return m_size;
}

END_OGS_NAMESPACE