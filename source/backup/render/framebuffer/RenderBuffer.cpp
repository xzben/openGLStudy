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

bool RenderBuffer::init(RenderBufferType type, bool mutilesampe)
{
	m_type = type;
	auto size = Window::getInstance()->getWinSize();

	glBindRenderbuffer(GL_RENDERBUFFER,m_rbo);
	switch (type)
	{
	case RenderBufferType::DEPATH_ATTATCHMENT:
		if(mutilesampe)
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH, size.width, size.height);
		else
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH, size.width, size.height);
		break;
	case RenderBufferType::STENCIL_ATTATCHMENT:
		if (mutilesampe)
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_STENCIL, size.width, size.height);
		else
			glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL, size.width, size.height);
		break;
	case RenderBufferType::DEPATH_STENCIL_ATTATCHMENT:
		if (mutilesampe)
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, size.width, size.height);
		else
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.width, size.height);
		break;
	}
	
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	return true;
}

END_NAMESPACE