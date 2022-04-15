#ifndef __2022_04_11_RENDER_BUFFER_H__
#define __2022_04_11_RENDER_BUFFER_H__

#include "common.h"
#include "base/Object.h"
#include "base/NonCopyable.h"

BEGIN_NAMESPACE

enum class RenderBufferType
{
	DEPATH_ATTATCHMENT = GL_DEPTH_ATTACHMENT,
	STENCIL_ATTATCHMENT = GL_STENCIL_ATTACHMENT,
	DEPATH_STENCIL_ATTATCHMENT = GL_DEPTH_STENCIL_ATTACHMENT,
};

class RenderBuffer : public Object, public NonCopyable
{
protected:
	GL_HANDLE m_rbo;
	RenderBufferType m_type;
public:
	friend class FrameBuffer;
	RenderBuffer();
	virtual ~RenderBuffer();

	bool init(RenderBufferType type, bool mutilesampe);
};
END_NAMESPACE
#endif//__2022_04_11_RENDER_BUFFER_H__