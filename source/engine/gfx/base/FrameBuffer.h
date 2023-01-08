#pragma once

#include "GfxObject.h"

BEGIN_OGS_GFX_NAMESPACE

class RenderPass;
class Texture;

class FrameBufferInfo
{
public:
	AutoRef<RenderPass> renderPass;
	std::vector<AutoRef<Texture>> colorTextures;
	AutoRef<Texture> depthStencilTexture;
};

class FrameBuffer : public GfxObject
{
	DECLARE_RUNTIME_CLASS(FrameBuffer)
public:
	FrameBuffer() :GfxObject(ObjectType::FRAMEBUFFER) {}
	virtual ~FrameBuffer() {};

protected:
	AutoRef<RenderPass> m_renderpass;
	std::vector<AutoRef<Texture>> m_colorTextures;
	AutoRef<Texture> m_depthStencilTexture;
};

END_OGS_GFX_NAMESPACE