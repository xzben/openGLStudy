#include "RenderBuffer.h"
#include "window/Window.h"
BEGIN_NAMESPACE


RenderBuffer::RenderBuffer()
{
	glGenRenderbuffers(1, &m_rbo);
}

RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &m_rbo);
	m_rbo = -1;
}

bool RenderBuffer::initDepth24Stencil8()
{
	auto size = Window::getInstance()->getWinSize();

	glBindRenderbuffer(GL_RENDERBUFFER,m_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.width, size.height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	return true;
}

END_NAMESPACE