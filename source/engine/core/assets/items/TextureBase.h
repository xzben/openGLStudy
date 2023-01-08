#pragma once

#include "Asset.h"
#include "gfx/base/states/sampler.h"

BEGIN_OGS_GFX_NAMESPACE
class Texture;
END_OGS_GFX_NAMESPACE
BEGIN_OGS_NAMESPACE

class TextureBase : public Asset
{
	DECLARE_CLASS(TextureBase)
	DECLARE_REFLEX_CLASS_FIELD(TextureBase)
public:
	TextureBase();
	virtual ~TextureBase();
	virtual void onLoad(const AutoRef<Data>& data)override;
	virtual void onUnload()override;

	void setWrapMode(WrapMode wrapS, WrapMode wrapT);
	void setWrapMode(WrapMode wrapS, WrapMode wrapT, WrapMode wrapR);
	void setFilters(Filter minFilter, Filter magFilter);
	void setMipFilter(Filter mipFilter);
	void setAnisotropy(uint32 anisotropy);
	HASH_CODE getHash() { return m_textureHash; }
	Gfx::Texture* getGfxTexture() { return nullptr; }
	AutoRef<Gfx::SamplerInfo> getSampeInfo() { return m_sampleInfo.get(); }
	AutoRef<Gfx::Sampler> getGfxSampler();
protected:
	int m_width{1};
	int m_height{1};
	PixelFormat m_format{PixelFormat::RGBA8888};
	WrapMode m_wrapS{WrapMode::REPEAT};
	WrapMode m_wrapT{ WrapMode::REPEAT };
	WrapMode m_wrapR{ WrapMode::REPEAT };
	Filter m_minFilter{Filter::LINEAR};
	Filter m_magFilter{ Filter::LINEAR };
	Filter m_mipFilter{ Filter::NONE };
	uint32 m_anisotropy = 0;
	AutoRef<Gfx::SamplerInfo> m_sampleInfo;
	AutoRef<Gfx::Sampler> m_gfxSampler;
	std::string m_id;
	HASH_CODE m_textureHash;
};

END_OGS_NAMESPACE