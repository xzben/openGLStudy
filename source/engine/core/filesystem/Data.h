#pragma once

#include "common.h"
#include "core/base/Object.h"
#include "core/memory/MemoryPool.h"

BEGIN_OGS_NAMESPACE

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

	int writeBuff(const byte* dest, int size);
	int writeOffset(int offset);
	
	bool readByte(byte& value);
	bool writeByte(const byte& value);

	bool readInt16(int16& value);
	bool writeInt16(const int16& value);

	bool readUInt16(uint16& value);
	bool writeUInt16(const uint16& value);

	bool readInt32(int32& value);
	bool writeInt32(const int32& value);

	bool readInt64(int64& value);
	bool writeInt64(const int64& value);

	bool readUInt32(uint32& value);
	bool writeUInt32(const uint32& value);

	bool readUInt64(uint64& value);
	bool writeUInt64(const uint64& value);

	bool readFloat(float& value);
	bool writeFloat(float& value);

	bool readDouble(double& value);
	bool writeDouble(const double& value);

	bool readString(std::string& value);
	bool writeString(const std::string& value);

	void resetReadOffset() { m_rIndex = 0; }
	void resetWriteOffset() { m_size = 0; }
	void resetBuffer() { resetReadOffset(); resetWriteOffset(); }
	uint32 writeableSize()
	{
		return m_capacity - m_size;
	}

	uint32 readableSize()
	{
		return m_size - m_rIndex;
	}
private:
	inline bool readUnionData(void* data, uint32 size);
	inline bool writeUnionData(void* data, uint32 size);
private:
	byte* m_data{ nullptr };
	uint32 m_capacity{ 0 };
	uint32 m_size{ 0 };
	uint32 m_rIndex{ 0 };
};

END_OGS_NAMESPACE