#include "GL3Texture.h"
#include "glad/glad.h"
#include "core/assets/AssetsMgr.h"
#include "core/assets/AssetItems.h"
BEGIN_OGS_GFX_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(GL3Texture)

uint32 getGLFormat(Format format) 
{
	switch (format)
	{
	case Format::RGB8:
		return GL_RGB;
	case Format::RGBA8:
		return GL_RGBA;
	case Format::DEPTH_STENCIL:
		return GL_DEPTH24_STENCIL8;
	}

	return GL_RGB;
}

GL3Texture::GL3Texture()
{
	glGenTextures(1, &m_handle);
}

GL3Texture::~GL3Texture()
{
	glDeleteTextures(1, &m_handle);
}

void GL3Texture::initialize(TextureInfo* info)
{
	m_info = info;
	uint32 gformat = getGLFormat(m_info->format);
	glBindTexture(GL_TEXTURE_2D, m_handle);
	glTexImage2D(GL_TEXTURE_2D, 0, gformat, info->width, info->height, 0, gformat, GL_UNSIGNED_BYTE, NULL);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void GL3Texture::initialize(const std::string& filename)
{
	AssetImage* img = AssetsMgr::getInstance()->getAsset<AssetImage>(filename, true);
	m_image = img;
	m_info = new TextureInfo();
	m_info->width = img->getWidth();
	m_info->height = img->getHeight();
	m_info->setFormat(img->getFormat());
	glBindTexture(GL_TEXTURE_2D, m_handle);
	uint32 gformat = getGLFormat(m_info->format);
	glTexImage2D(GL_TEXTURE_2D, 0, gformat, m_info->width, m_info->height, 0, gformat, GL_UNSIGNED_BYTE, img->getImageData());
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void GL3Texture::resize(uint32 width, uint32 height)
{
	Super::resize(width, height);
	glBindTexture(GL_TEXTURE_2D, m_handle);
	uint32 gformat = getGLFormat(m_info->format);
	glTexImage2D(GL_TEXTURE_2D, 0, gformat, m_info->width, m_info->height, 0, gformat, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
}

END_OGS_GFX_NAMESPACE