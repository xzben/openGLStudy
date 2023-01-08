#include "SimpleTexture.h"
#include "AssetImage.h"
#include "gfx/Device.h"

BEGIN_OGS_NAMESPACE

IMPLEMENT_CLASS(SimpleTexture)

BEGIN_REFLEX_CLASS_FIELD(SimpleTexture)
END_REFLEX_CLASS_FIELD()

uint32 getMipLevel(uint32 width, uint32 height) {
	uint32 size = std::max(width, height);
	uint32 level = 0;
	while (size) {
		size >>= 1;
		level++;
	}
	return level;
}

bool isPOT(uint32 n) { return n && (n & (n - 1)) == 0; }
bool canGenerateMipmap(uint32 w, uint32 h) {
	return isPOT(w) && isPOT(h);
}

SimpleTexture::SimpleTexture()
{

}

SimpleTexture::~SimpleTexture()
{

}

void SimpleTexture::updateData(const byte* data, uint32 level /* =0 */, uint32 index /* =0*/)
{
	if (m_gfxTexture == nullptr || m_mipmapLevel <= level) return;


}
void SimpleTexture::assignImage(AssetImage* image, uint32 level, uint32 index /* = 0 */)
{
	const byte* data = image->getImageData();
	if (data == nullptr) return;
	updateData(data, level, index);
	m_loaded = true;
}

void SimpleTexture::createTexture()
{
	if (m_width == 0 || m_width == 0) return;
	auto flags = Gfx::TextureFlagBit::NONE;
	if (m_mipFilter != Filter::NONE && canGenerateMipmap(m_width, m_height))
	{
		m_mipmapLevel = getMipLevel(m_width, m_height);
		if (!isUsingOfflineMipmaps())
		{
			flags = Gfx::TextureFlagBit::GEN_MIPMAP;
		}
	}

	Gfx::Device* device = Gfx::Device::getInstance();
	//device->createTexture();


}
void SimpleTexture::setMipRange(uint16 baseLevel, uint16 maxLevel)
{
	m_baseLevel = baseLevel < 1 ? 0 : baseLevel;
	m_maxLvel = maxLevel < 1 ? 0 : maxLevel;
}

void SimpleTexture::setMipmapLevel(uint32 level)
{
	m_mipmapLevel = level < 1 ? 1 : level;
}

END_OGS_NAMESPACE