#include "GL3Texture.h"
#include "glad/glad.h"

BEGIN_OGS_GFX_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(GL3Texture)

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

}


END_OGS_GFX_NAMESPACE