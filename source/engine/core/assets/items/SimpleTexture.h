#pragma once

#include "TextureBase.h"

BEGIN_OGS_GFX_NAMESPACE
class Texture;
END_OGS_GFX_NAMESPACE

BEGIN_OGS_NAMESPACE

class AssetImage;

class SimpleTexture : public TextureBase
{
	DECLARE_CLASS(SimpleTexture)
	DECLARE_REFLEX_CLASS_FIELD(SimpleTexture)
public:
	SimpleTexture();
	virtual ~SimpleTexture();

	void updateData(const byte* data, uint32 level = 0, uint32 index = 0);
	void assignImage(AssetImage* image, uint32 level, uint32 index = 0);

	void setMipRange(uint16 baseLevel, uint16 maxLevel);
	void setMipmapLevel(uint32 level);
protected:
	void createTexture();
	bool isUsingOfflineMipmaps() { return false; }
protected:
	AutoRef<Gfx::Texture> m_gfxTexture;
	bool m_loaded;
	uint16 m_mipmapLevel{ 1 };
	uint16 m_baseLevel{ 0 };
	uint16 m_maxLvel{ 1000 };
};
END_OGS_NAMESPACE