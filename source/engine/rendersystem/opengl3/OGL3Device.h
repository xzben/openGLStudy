#pragma once

#include "rendersystem/GfxDevice.h"

BEGIN_OGS_NAMESPACE
class OGL3Device : public GfxDevice
{
	DECLARE_RUNTIME_CLASS(OGL3Device)
public:
	virtual bool init() override;
	virtual void processEvent() override;
	virtual void swapFrameBuffer()override;
	virtual void GetScreenSize(int& width, int& height) override;
};
END_OGS_NAMESPACE