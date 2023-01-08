#include "TextureBase.h"
#include "utils/IDGenerator.h"
#include "gfx/base/gfx_base_define.h"
#include "gfx/Device.h"
BEGIN_OGS_NAMESPACE

static IDGenerator textIdGenerator("Tex");

IMPLEMENT_RUNTIME_CLASS(TextureBase)

BEGIN_REFLEX_CLASS_FIELD(TextureBase)
END_REFLEX_CLASS_FIELD()

TextureBase::TextureBase()
{
	m_id = textIdGenerator.getNewId();
	m_textureHash = 666;
	m_sampleInfo = new Gfx::SamplerInfo;
	Utils::hash_combine<std::string>(m_textureHash, m_id);
}

TextureBase::~TextureBase()
{

}

AutoRef<Gfx::Sampler> TextureBase::getGfxSampler()
{
	if (m_gfxSampler == nullptr)
	{
		m_gfxSampler = Gfx::Device::getInstance()->getSampler(m_sampleInfo.get());
	}

	return m_gfxSampler;
}

void TextureBase::setWrapMode(WrapMode wrapS, WrapMode wrapT)
{
	setWrapMode(wrapS, wrapT, wrapS);
}

void TextureBase::setWrapMode(WrapMode wrapS, WrapMode wrapT, WrapMode wrapR)
{
	m_wrapS = wrapS;
	m_wrapT = wrapT;
	m_wrapR = wrapR;
	m_sampleInfo->addressU = (Gfx::Address)wrapS;
	m_sampleInfo->addressV = (Gfx::Address)wrapT;
	m_sampleInfo->addressW = (Gfx::Address)wrapR;
}

void TextureBase::setFilters(Filter minFilter, Filter magFilter)
{
	m_minFilter = minFilter;
	m_magFilter = magFilter;

	m_sampleInfo->minFilter = (Gfx::Filter)minFilter;
	m_sampleInfo->magFilter = (Gfx::Filter)magFilter;
}

void TextureBase::setMipFilter(Filter mipFilter)
{
	m_mipFilter = mipFilter;
	m_sampleInfo->mipFilter = (Gfx::Filter)mipFilter;
}

void TextureBase::setAnisotropy(uint32 anisotropy)
{
	m_anisotropy = anisotropy;
	m_sampleInfo->maxAnisotropy = anisotropy;
}

void TextureBase::onLoad(const AutoRef<Data>& data)
{

}

void TextureBase::onUnload()
{

}

END_OGS_NAMESPACE