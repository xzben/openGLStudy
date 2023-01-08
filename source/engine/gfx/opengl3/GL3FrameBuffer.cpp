#include "GL3FrameBuffer.h"
#include "glad/glad.h"
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

END_OGS_GFX_NAMESPACE