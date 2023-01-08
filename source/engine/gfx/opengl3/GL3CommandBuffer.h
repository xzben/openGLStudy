#pragma once
#include "gfx/base/CommandBuffer.h"
#include "gl3_define.h"

BEGIN_OGS_GFX_NAMESPACE

class GL3CommandBuffer : public CommandBuffer
{
	DECLARE_RUNTIME_CLASS(GL3CommandBuffer)
public:
	GL3CommandBuffer();
	virtual ~GL3CommandBuffer();
protected:

};
END_OGS_GFX_NAMESPACE