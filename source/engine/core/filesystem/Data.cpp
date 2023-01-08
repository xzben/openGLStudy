#include "Data.h"
#include <cstdio>
BEGIN_OGS_NAMESPACE

#define MIN_DATA_BUFF  64

union unionData
{
	short int16value;
	uint16 uint16value;
	int32 int32Value;
	uint32 uint32Value;
	int64  int64Value;
	uint64 uint64Value;
	float  floatValue;
	double doubleValue;
	byte  datas[8];
};

//判断当前是否是小端模式
constexpr bool is_little_endian2(void)
{
	int a = 0x12345678;
	char b = *((char*)(&a));		// 指针方式其实就是共用体的本质
	if (0x78 == b)
		return true;
	else if (0x12 == b)
		return false;

	return true;
}
const bool isLittleEndian = is_little_endian2();

Data::Data()
{
}

Data::~Data()
{
	SAFE_DELTE(m_data);
}

void Data::reverse(int size)
{
	if (size <= m_capacity) return;
	int oldsize = m_capacity;
	if (m_capacity <= 0)
		m_capacity = MIN_DATA_BUFF;

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

int  Data::writeBuff(const byte* src, int size)
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

bool Data::readByte(byte& value)
{
	if (readableSize() < 1) return false;
	readBuff(&value, 1);

	return true;
}

bool Data::writeByte(const byte& value)
{
	writeBuff(&value, 1);
	return true;
}

bool Data::readUnionData(void* vdata, uint32 size)
{
	if (readableSize() < size) return false;
	unionData* data = (unionData*)vdata;
	readBuff(data->datas, size);

	if (!isLittleEndian)
	{
		byte tmp;
		int swapIndex;
		for (int i = 0; i < size/2; i++)
		{
			swapIndex = size - i - 1;
			tmp = data->datas[i];
			data->datas[i] = data->datas[swapIndex];
			data->datas[swapIndex] = tmp;
		}
	}

	return true;
}

bool Data::writeUnionData(void* vdata, uint32 size)
{
	unionData* data = (unionData*)vdata;
	if (!isLittleEndian)
	{
		byte tmp;
		int swapIndex;
		for (int i = 0; i < size / 2; i++)
		{
			swapIndex = size - i - 1;
			tmp = data->datas[i];
			data->datas[i] = data->datas[swapIndex];
			data->datas[swapIndex] = tmp;
		}
	}
	writeBuff(data->datas, size);

	return true;
}

bool Data::readInt16(int16& value)
{
	unionData data;
	if (readUnionData(&data, sizeof(int16))) return false;
	
	value = data.int16value;

	return true;
}

bool Data::writeInt16(const int16& value)
{
	unionData data;
	data.int16value = value;
	return writeUnionData(&data, sizeof(int16));
}

bool Data::readUInt16(uint16& value)
{
	unionData data;
	if (readUnionData(&data, sizeof(uint16))) return false;

	value = data.uint16value;

	return true;
}

bool Data::writeUInt16(const uint16& value)
{
	unionData data;
	data.uint16value = value;
	return writeUnionData(&data, sizeof(uint16));
}

bool Data::readInt32(int32& value)
{
	unionData data;
	if (readUnionData(&data, sizeof(int32))) return false;

	value = data.int32Value;
	return true;
}

bool Data::writeInt32(const int32& value)
{
	unionData data;
	data.int32Value = value;
	return writeUnionData(&data, sizeof(short));
}

bool Data::readInt64(int64& value)
{
	unionData data;
	if (readUnionData(&data, sizeof(int64))) return false;

	value = data.int64Value;
	return true;
}

bool Data::writeInt64(const int64& value)
{
	unionData data;
	data.int64Value = value;
	return writeUnionData(&data, sizeof(short));
}

bool Data::readUInt32(uint32& value)
{
	unionData data;
	if (readUnionData(&data, sizeof(uint32))) return false;

	value = data.uint32Value;
	return true;
}
bool Data::writeUInt32(const uint32& value)
{
	unionData data;
	data.uint32Value = value;
	return writeUnionData(&data, sizeof(short));
}

bool Data::readUInt64(uint64& value)
{
	unionData data;
	if (readUnionData(&data, sizeof(uint64))) return false;

	value = data.uint64Value;
	return true;
}

bool Data::writeUInt64(const uint64& value)
{
	unionData data;
	data.uint64Value = value;
	return writeUnionData(&data, sizeof(short));
}

bool Data::readFloat(float& value)
{
	unionData data;
	if (readUnionData(&data, sizeof(float))) return false;

	value = data.floatValue;
	return true;
}
bool Data::writeFloat(float& value)
{
	unionData data;
	data.floatValue = value;
	return writeUnionData(&data, sizeof(short));
}
bool Data::readDouble(double& value)
{
	unionData data;
	if (readUnionData(&data, sizeof(double))) return false;

	value = data.doubleValue;
	return true;
}

bool Data::writeDouble(const double& value)
{
	unionData data;
	data.doubleValue = value;
	return writeUnionData(&data, sizeof(short));
}

bool Data::readString(std::string& value)
{
	uint32 len;
	if (!readUInt32(len))
	{
		return false;
	}
	if (readableSize() < len) return false;
	value.reserve(len);
	readBuff((byte*)value.data(), len);

	return true;
}

bool Data::writeString(const std::string& value)
{
	uint32 len = value.length();
	writeUInt32(len);
	const char* pstr = value.c_str();
	writeBuff((byte*)pstr, len);
	
	return true;
}

END_OGS_NAMESPACE