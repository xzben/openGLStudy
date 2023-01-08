#include "RenderBuffer.h"
#include "core/base/GameApp.h"
#include "core/view/GameView.h"
#include "core/math/math.h"
#include "core/view/Screen.h"
BEGIN_OGS_NAMESPACE

RenderBuffer::RenderBuffer(Size* psize /* = nullptr */)
{
	m_size = psize == nullptr ? Screen::getSize() : *psize;
	glGenRenderbuffers(1, &m_handle);
}

RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &m_handle);
	m_handle = INVALID_HANDLE;
}

void RenderBuffer::active()
{
	glBindRenderbuffer(GL_RENDERBUFFER, m_handle);
}

void RenderBuffer::deactive()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RenderBuffer::setSize(const Size& size)
{
	if (m_size == size) return;
	m_size = size;
	initAsDepthStencil();
}

void RenderBuffer::initAsDepthStencil()
{
	glBindRenderbuffer(GL_RENDERBUFFER, m_handle);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_size.width, m_size.height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
END_OGS_NAMESPACE