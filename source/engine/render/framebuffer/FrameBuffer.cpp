#include "FrameBuffer.h"
#include "render/Texture.h"

BEGIN_NAMESPACE

FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &m_fbo);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_fbo);
}

void FrameBuffer::active()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void FrameBuffer::addColorAttachment(Texture* tex)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex->m_texture, 0);
}

void FrameBuffer::addDepthAttachment(Texture* tex)
{

}
END_NAMESPACE