#pragma once

#include "gfx/base/RenderPass.h"
#include "gl3_define.h"

BEGIN_OGS_GFX_NAMESPACE

class GL3RenderPass : public RenderPass
{
	DECLARE_RUNTIME_CLASS(GL3RenderPass)
public:
	GL3RenderPass();
	virtual ~GL3RenderPass();

protected:
};
END_OGS_GFX_NAMESPACE