#pragma once

#include "rendersystem/GfxDevice.h"

BEGIN_OGS_NAMESPACE
class OGL3Device : public GfxDevice
{
public:
	virtual void swapFrameBuffer()override;
};
END_OGS_NAMESPACE