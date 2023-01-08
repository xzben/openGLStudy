#pragma once

#include "gfx/base/GfxObject.h"

BEGIN_OGS_GFX_NAMESPACE

class Queue;

class TextureBarrierInfo
{
public:
	AccessFlagBit prevAccesses;
	AccessFlagBit nextAccesses;
	BarrierType   type;
	uint32        baseMipLevel;
	uint32		  levelCount;
	uint32		  baseSlice;
	uint32		  sliceCount;
	bool          discardContents;
	WeakRef<Queue> srcQueue;
	WeakRef<Queue> dstQueue;
};

class TextureBarrier : public GfxObject
{
	DECLARE_RUNTIME_CLASS(TextureBarrier)
public:
	TextureBarrier() :GfxObject(ObjectType::TEXTURE_BARRIER) {}
	virtual ~TextureBarrier() {}
};

END_OGS_GFX_NAMESPACE