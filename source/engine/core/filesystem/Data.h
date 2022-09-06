#pragma once

#include "common.h"
#include "core/base/Object.h"
#include "core/memory/MemoryPool.h"

BEGIN_OGS_NAMESPACE

#define MIN_DATA_BUFF  64

class Data : public Object
{
public:
	Data();
	~Data();
	void reverse(int size);

	int getSize() { return m_size; }
	byte* getData() { return m_data; }

	int readBuff(byte* dest, int size);
	int readOffset(int offet);

	int writeBuff(byte* dest, int size);
	int writeOffset(int offset);
	
	void resetReadOffset() { m_rIndex = 0; }
	void resetWriteOffset() { m_size = 0; }
	void resetBuffer() { resetReadOffset(); resetWriteOffset(); }
private:
	byte* m_data{ nullptr };
	int m_capacity{ 0 };
	int m_size{ 0 };
	int m_rIndex{ 0 };
};

END_OGS_NAMESPACE