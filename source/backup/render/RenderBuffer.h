#pragma once

#include "define.h"
#include "core/base/Object.h"
#include "core/render/render_macro.h"
#include "core/math/math.h"
BEGIN_OGS_NAMESPACE

class RenderBuffer : public Object
{
public:
	friend class FrameBuffer;
	RenderBuffer(Size* psize = nullptr);
	~RenderBuffer();
	inline void active();
	inline void deactive();
	void setSize(const Size& size);
protected:
	void initAsDepthStencil();
protected:
	Size m_size;
	RenderHandle m_handle;
};
END_OGS_NAMESPACE