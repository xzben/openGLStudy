#include "FrameBuffer.h"

BEGIN_OGS_GFX_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(FrameBuffer)


bool FrameBuffer::initilize(FrameBufferInfo& info)
{
	m_renderpass = info.renderPass;
	m_colorTextures = info.colorTextures;
	m_depthStencilTexture = info.depthStencilTexture;

	return true;
}

bool FrameBuffer::initilize(Texture* color, Texture* depthStencil)
{
	m_colorTextures.clear();
	m_colorTextures.push_back(color);
	m_depthStencilTexture = depthStencil;

	return true;
}
END_OGS_GFX_NAMESPACE