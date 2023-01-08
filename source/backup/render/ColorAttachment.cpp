#include "ColorAttachment.h"
#include "core/view/Screen.h"
BEGIN_OGS_NAMESPACE

ColorAttachment::ColorAttachment()
{
	glGenTextures(1, &m_handle);
}

ColorAttachment::~ColorAttachment()
{
	glDeleteTextures(1, &m_handle);
	m_handle = INVALID_HANDLE;
}

void ColorAttachment::handleInit()
{
	//m_size = psize == nullptr ? Screen::getSize() : *psize;
	//m_sampeinfo = SampleInfo::DefaultColorAttachment;
	//m_usage = TextureUsage::COLOR_ATTACHMENT;

	//glBindTexture(GL_TEXTURE_2D, m_handle);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.width, m_size.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	//updateSampeInfo();
	//glBindTexture(GL_TEXTURE_2D, 0);
}

END_OGS_NAMESPACE