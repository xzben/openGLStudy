#pragma once

#include "gfx/base/GfxObject.h"

BEGIN_OGS_GFX_NAMESPACE

class Queue;

class BufferBarrierInfo
{
public:
	AccessFlagBit preAccesses;
	AccessFlagBit nextAccesses;
	BarrierType   type;
	uint32		  offset;
	uint32		  size;
	bool		  discardContents;
	WeakRef<Queue> srcQueue;
	WeakRef<Queue> dstQueue;
};

class BufferBarrier : public GfxObject
{
	DECLARE_RUNTIME_CLASS(BufferBarrier)
public:
	BufferBarrier() :GfxObject(ObjectType::BUFFER_BARRIER) {}
	virtual ~BufferBarrier() {}
};
END_OGS_GFX_NAMESPACE