#include "GL3FrameBuffer.h"
#include "glad/glad.h"
#include "gfx/base/Texture.h"
#include "gfx/opengl3/GL3Texture.h"
BEGIN_OGS_GFX_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(GL3FrameBuffer)

GL3FrameBuffer::GL3FrameBuffer()
{
	glGenFramebuffers(1, &m_handle);
}

GL3FrameBuffer::~GL3FrameBuffer()
{
	glDeleteFramebuffers(1, &m_handle);
}

bool GL3FrameBuffer::initilize(Texture* color, Texture* depthStencil)
{
	Super::initilize(color, depthStencil);
	return doInit();
}

bool GL3FrameBuffer::doInit()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
	AutoRef<Texture> color = color;
	AutoRef<GL3Texture> gTx = color.ToCast<GL3Texture>();
	AutoRef<TextureInfo> txinfo = color->getTextureInfo();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, txinfo->width, txinfo->height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gTx->getHandle(), 0);

	AutoRef<GL3Texture> gDepthTx = m_depthStencilTexture.ToCast<GL3Texture>();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, gDepthTx->getHandle(), 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		CCLOG("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

bool GL3FrameBuffer::initilize(FrameBufferInfo& info)
{
	Super::initilize(info);
	return doInit();
}

bool GL3FrameBuffer::active()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
	return true;
}

void GL3FrameBuffer::deactive()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

END_OGS_GFX_NAMESPACE