#pragma once

#include "GfxObject.h"

namespace OGS
{
	class Data;
}

BEGIN_OGS_GFX_NAMESPACE

class BufferInfo
{
public:
	BufferUsageBit usage;
	MemoryUsageBit memUsage;
	uint32 size;
	uint32 stride;
	BufferFlagBit flags;
};

class Buffer : public GfxObject
{
	DECLARE_RUNTIME_CLASS(Buffer)
public:
	Buffer():GfxObject(ObjectType::BUFFER){}
	virtual void initialize(const BufferInfo& info)
	{
		m_usage = info.usage;
		m_memUsage = info.memUsage;
		m_size = info.size;
		m_stride = info.stride;
		m_count = 1;
		m_flag = info.flags;
	}

	virtual void active() = 0;
	virtual void deactive() = 0;
	virtual bool updateBuffer(void* data, uint32 size) = 0;
	virtual bool updateSubBuffer(void* data, uint32 offset, uint32 size) = 0;
	virtual ~Buffer(){}
	uint32 getStride() { return m_stride; }
protected:
	BufferUsageBit m_usage{BufferUsageBit::NONE};
	MemoryUsageBit m_memUsage{ MemoryUsageBit::NONE };
	uint32 m_size{ 0 };
	uint32 m_stride{ 1 };
	uint32 m_count{ 0 };
	BufferFlagBit m_flag{ BufferFlagBit::NONE };
};

END_OGS_GFX_NAMESPACE