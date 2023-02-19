#pragma once

#include "GfxObject.h"

namespace OGS
{
	class AssetImage;
}

BEGIN_OGS_GFX_NAMESPACE

class TextureInfo : public Object
{
	DECLARE_RUNTIME_CLASS(TextureInfo)
public:
	void setFormat(PixelFormat format);
	Format getFormat();
	TextureType type{ TextureType::TEX2D };
	TextureUsageBit usage{ TextureUsageBit::NONE };
	Format  format{ Format::UNKNOWN };
	uint16  width{0};
	uint16  height{0};
	TextureFlagBit flags{ TextureFlagBit::NONE };
	uint16 layerCount{ 1 };
	uint8  levelCount{ 1 };
	SampleCount samples{ SampleCount::ONE };
	uint8 depth{1};
	uint8 externalRes{0};
};

class Texture;

class TextureViewInfo : public Object
{
	DECLARE_RUNTIME_CLASS(TextureViewInfo)
public:
	WeakRef<Texture> texture;
	TextureType		 type;
	Format           format;
	int32			 baseLevel;
	int32			 levelCount;
	int32            baseLayer;
	int32            layerCount;
};

class Texture : public GfxObject
{
	DECLARE_RUNTIME_CLASS(Texture)
public:
	Texture() :GfxObject(ObjectType::TEXTURE){};
	virtual ~Texture() {}

	virtual uint32 getHandle() { return 0; }
	virtual void resize(uint32 width, uint32 height);
	uint32 getLevelCount(uint32 width, uint32 height);
	AutoRef<TextureInfo> getTextureInfo() { return m_info; }
protected:
	AutoRef<AssetImage> m_image;
	AutoRef<TextureInfo> m_info;
	AutoRef<Texture> m_color;
	AutoRef<TextureViewInfo> m_viewInfo;
	bool	m_isPowerOf2{ false };
	uint32  m_size{ 0 };
};

END_OGS_GFX_NAMESPACE