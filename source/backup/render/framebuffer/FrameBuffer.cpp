#include "FrameBuffer.h"
#include "render/Texture.h"
#include "window/Window.h"

BEGIN_NAMESPACE

FrameBuffer::FrameBuffer(bool mutilesample)
	: m_mutilesampe(mutilesample)
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

void FrameBuffer::deactive()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Texture* FrameBuffer::addColorAttachment()
{
	Texture* tex = new Texture();
	auto size = Window::getInstance()->getWinSize();
	tex->initAttachment(size.width, size.height);
	int count = this->m_colorAttachs.size();
	this->m_colorAttachs.push_back(tex);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + count, GL_TEXTURE_2D, tex->m_texture, 0);

	return tex;
}

Texture* FrameBuffer::addDepthAttachment()
{
	Texture* tex = new Texture();
	auto size = Window::getInstance()->getWinSize();
	tex->initAttachment(size.width, size.height);
	
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex->m_texture, 0);
	this->m_depathAttach = tex;

	return tex;

}

Texture* FrameBuffer::addStencilAttachment()
{
	Texture* tex = new Texture();
	auto size = Window::getInstance()->getWinSize();
	tex->initAttachment(size.width, size.height);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, tex->m_texture, 0);
	this->m_stencilAttach = tex;

	return tex;
}

Texture* FrameBuffer::addDepthStencilAttatchment()
{
	Texture* tex = new Texture();
	auto size = Window::getInstance()->getWinSize();
	tex->initDepthStencilAttachment(size.width, size.height);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, tex->m_texture, 0);
	this->m_stencilAttach = tex;
	this->m_depathAttach = tex;

	return tex;
}

void FrameBuffer::addDepthAttachment(RenderBuffer* rb)
{
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, (uint)rb->m_type, GL_RENDERBUFFER, rb->m_rbo);
}

bool FrameBuffer::checkComplete()
{
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		return true;
	}

	return false;
}
END_NAMESPACE