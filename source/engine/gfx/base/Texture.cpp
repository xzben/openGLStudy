#include "Texture.h"

BEGIN_OGS_GFX_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(TextureInfo)
IMPLEMENT_RUNTIME_CLASS(Texture)

void TextureInfo::setFormat(PixelFormat pformat)
{
	switch (pformat)
	{
	case PixelFormat::RGB888:
	{
		format = Format::RGB8;
		break;
	}
	case PixelFormat::RGBA8888:
		format = Format::RGBA8;
		break;
	default:
		format = Format::RGB8;
	}
}

Format TextureInfo::getFormat()
{
	switch (usage)
	{
	case OGS::Gfx::TextureUsageBit::COLOR_ATTACHMENT:
	{
		return Format::RGB8;
	}
	case OGS::Gfx::TextureUsageBit::DEPTH_STENCIL_ATTACHMENT:
		return Format::DEPTH_STENCIL;
	}

	return format;
}
void Texture::resize(uint32 width, uint32 height)
{
	m_info->width = width;
	m_info->height = height;
}

uint32 Texture::getLevelCount(uint32 width, uint32 height)
{
	return 0;
}

END_OGS_GFX_NAMESPACE