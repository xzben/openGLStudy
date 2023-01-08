#include "FrameBuffer.h"
#include "core/base/GameApp.h"
#include "core/view/GameView.h"
#include "core/render/Texture.h"
#include "core/render/RenderBuffer.h"
#include "core/view//Screen.h"
#include <glad/glad.h>

BEGIN_OGS_NAMESPACE

FrameBuffer::FrameBuffer(Size* size /* = nullptr */)
{
	m_size = size == nullptr ? Screen::getSize() : *size;
	init();
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_handle);
	m_handle = INVALID_HANDLE;
}

void FrameBuffer::setSize(const Size& size)
{
	if (m_size == size) return;
	m_size = size;
	for (auto it = m_colorTextures.begin(); it != m_colorTextures.end(); it++)
	{
		(*it)->setSize(size);
	}
	if (m_rbDepthStencil) m_rbDepthStencil->setSize(size);
	if (m_textureDepthStencil) m_textureDepthStencil->setSize(size);
}

bool FrameBuffer::init()
{
	glGenFramebuffers(1, &m_handle);
	addAttachment(AttachmentType::COLOR_ATTACHMENT, Texture::createAttatchColor(&m_size));
	addAttachment(AttachmentType::DEPTH_24_STENCIL8_ATTACHMENT, new RenderBuffer(&m_size));

	if (isComplete())
	{
		return true;
	}

	return false;
}

void FrameBuffer::active()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
}

WeakRef<Texture> FrameBuffer::getColorTexture(int index)
{ 
	if (m_colorTextures.size() > index) 
		return m_colorTextures[index]; 

	return nullptr;
}

void FrameBuffer::deactive()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool FrameBuffer::isComplete()
{
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		return true;
	}
	else
	{
		ASSERT(false, "ERROR:: FrameBuffer is not complete!");
	}

	return false;
}

void FrameBuffer::addAttachment(AttachmentType type, Texture* texture)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
	switch (type)
	{
	case AttachmentType::COLOR_ATTACHMENT:
		{
			int size = m_colorTextures.size();
			m_colorTextures.push_back(texture);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + size, GL_TEXTURE_2D, texture->m_handle, 0);
			break;
		}
	case AttachmentType::DEPTH_24_STENCIL8_ATTACHMENT:
		{
			ASSERT(m_textureDepthStencil == nullptr && m_rbDepthStencil == nullptr, "depth stencil attachment repeat set");
			m_textureDepthStencil = texture;
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture->m_handle, 0);
			break;;
		}
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::addAttachment(AttachmentType type, RenderBuffer* renderbuffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
	switch (type)
	{
	case AttachmentType::DEPTH_24_STENCIL8_ATTACHMENT:
	{
		ASSERT(m_textureDepthStencil == nullptr && m_rbDepthStencil == nullptr, "depth stencil attachment repeat set");
		m_rbDepthStencil = renderbuffer;
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer->m_handle, 0);
		break;;
	}
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

END_OGS_NAMESPACE