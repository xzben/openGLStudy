#pragma once

#include "gfx/base/FrameBuffer.h"
#include "gl3_define.h"

BEGIN_OGS_GFX_NAMESPACE

class GL3FrameBuffer : public FrameBuffer
{
	DECLARE_RUNTIME_CLASS(GL3FrameBuffer)
public:
	GL3FrameBuffer();
	virtual ~GL3FrameBuffer();

	bool initilize(FrameBufferInfo& info);
	bool initilize(Texture* color, Texture* depthStencil);
	bool active();
	void deactive();
protected:
	bool doInit();
protected:
	OGL_HANDLE m_handle;
};
END_OGS_GFX_NAMESPACE