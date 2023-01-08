#pragma once

#include "gfx/base/Swapchain.h"
#include "gl3_define.h"

BEGIN_OGS_GFX_NAMESPACE

class GL3Swapchain : public Swapchain
{
	DECLARE_RUNTIME_CLASS(GL3Swapchain)
public:
	GL3Swapchain();
	virtual ~GL3Swapchain();
};
END_OGS_GFX_NAMESPACE