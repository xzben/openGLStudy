#ifndef __2022_04_11_RENDER_BUFFER_H__
#define __2022_04_11_RENDER_BUFFER_H__

#include "common.h"
#include "base/Object.h"
#include "base/NonCopyable.h"

BEGIN_NAMESPACE

class RenderBuffer : public Object, public NonCopyable
{
protected:
	GL_HANDLE m_rbo;
public:
	RenderBuffer();
	virtual ~RenderBuffer();

	bool initDepth24Stencil8();
};
END_NAMESPACE
#endif//__2022_04_11_RENDER_BUFFER_H__