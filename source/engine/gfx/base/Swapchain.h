#pragma once

#include "GfxObject.h"

BEGIN_OGS_GFX_NAMESPACE

class Texture;

class SwapchainInfo
{
public:
	uint32 width;
	uint32 height;
	VsyncMode vsyncMode;
};

class Swapchain : public GfxObject
{
	DECLARE_RUNTIME_CLASS(Swapchain)
public:
	Swapchain():GfxObject(ObjectType::SWAPCHAIN){}
	virtual ~Swapchain(){}

	SurfaceTransform m_transform{ SurfaceTransform::IDENTITY };
	AutoRef<Texture> m_colorTexture;
	AutoRef<Texture> m_depthStencilTexture;

};
END_OGS_GFX_NAMESPACE