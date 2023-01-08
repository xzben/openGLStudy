#pragma once

#include "gfx/base/GfxObject.h"

BEGIN_OGS_GFX_NAMESPACE

struct GeneralBarrierInfo
{
public:
	AccessFlagBit prevAccesses{ AccessFlagBit::NONE };
	AccessFlagBit nextAccesses{ AccessFlagBit::NONE };
	BarrierType   type = BarrierType::FULL;
};

class GeneralBarrier : public GfxObject
{
	DECLARE_RUNTIME_CLASS(GeneralBarrier)
public:
	GeneralBarrier() :GfxObject(ObjectType::GLOBAL_BARRIER) {}
	virtual ~GeneralBarrier() {}
};
END_OGS_GFX_NAMESPACE