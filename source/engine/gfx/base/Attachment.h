#pragma once

#include "common.h"
#include "gfx_base_define.h"

BEGIN_OGS_GFX_NAMESPACE
class GeneralBarrier;

class ColorAttachment
{
public:
	Format format{Format::UNKNOWN};
	SampleCount sampleCount{ SampleCount::ONE };
	LoadOp loadOp{ LoadOp::CLEAR };
	StoreOp storeOp{ StoreOp::STORE };
	AutoRef<GeneralBarrier> barrier;
	bool isGeneralLayout{ false };
};

class DepthStencilAttachment
{
public:
	Format format{ Format::UNKNOWN };
	SampleCount sampleCount{ SampleCount::ONE };
	LoadOp  depthLoadOp{ LoadOp::CLEAR };
	StoreOp depthStoreOp{ StoreOp::STORE };
	LoadOp  stencilLoadOp{ LoadOp::CLEAR };
	StoreOp stencilStoreOp{ StoreOp::STORE };
	AutoRef<GeneralBarrier> barrier;
	bool isGeneralLayout{ false };
};

END_OGS_GFX_NAMESPACE