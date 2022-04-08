#ifndef __2022_04_08_FRAME_BUFFER_H__
#define __2022_04_08_FRAME_BUFFER_H__
#include "common.h"
#include "base/Object.h"
#include "base/NonCopyable.h"

BEGIN_NAMESPACE

class Texture;

class FrameBuffer : public Object, public NonCopyable 
{
protected:
	GL_HANDLE m_fbo;
public:
	FrameBuffer();
	virtual ~FrameBuffer();

	virtual void active();

	void addColorAttachment(Texture* tex);
	void addDepthAttachment(Texture* tex);

};

END_NAMESPACE
#endif // !__2022_04_08_FRAME_BUFFER_H__