#pragma once

#include "define.h"
#include "core/render/render_macro.h"
#include "core/base/Object.h"
#include "core/math/math.h"
#include <vector>
BEGIN_OGS_NAMESPACE

class Texture;
class RenderBuffer;

class FrameBuffer : public Object
{
public:
	FrameBuffer(Size* size = nullptr);
	virtual ~FrameBuffer();

	bool init();
	void setSize(const Size& size);
	void active();
	void deactive();
	void addAttachment(AttachmentType type, Texture* texture);
	void addAttachment(AttachmentType type, RenderBuffer* renderbuffer);
	WeakRef<Texture> getColorTexture(int index);
	WeakRef<Texture> getDepthStencilTexture() { return m_textureDepthStencil; }
	WeakRef<RenderBuffer> getDepthStencilRenderbuffer() { return m_rbDepthStencil; }

protected:
	bool isComplete();
protected:
	Size m_size;
	std::vector<AutoRef<Texture>> m_colorTextures;
	RenderHandle m_handle{ INVALID_HANDLE };
	AutoRef<RenderBuffer> m_rbDepthStencil;
	AutoRef<Texture>      m_textureDepthStencil;

	
};

END_OGS_NAMESPACE