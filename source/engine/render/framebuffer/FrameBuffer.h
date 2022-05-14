#ifndef __2022_04_08_FRAME_BUFFER_H__
#define __2022_04_08_FRAME_BUFFER_H__
#include "common.h"
#include "base/Object.h"
#include "base/NonCopyable.h"
#include "RenderBuffer.h"
BEGIN_NAMESPACE

class Texture;

class FrameBuffer : public Object, public NonCopyable 
{
protected:
	GL_HANDLE m_fbo;
	std::vector<Texture*> m_colorAttachs;
	Texture* m_depathAttach;
	Texture* m_stencilAttach;
	bool m_mutilesampe;  //是否开启多重采样
public:
	FrameBuffer(bool mutilesample);
	virtual ~FrameBuffer();

	virtual void active();
	virtual void deactive();

	Texture* addColorAttachment();
	Texture* addDepthAttachment();
	Texture* addStencilAttachment();
	Texture* addDepthStencilAttatchment();

	void   addDepthAttachment(RenderBuffer* rb);

protected:
	bool checkComplete();
};

END_NAMESPACE
#endif // !__2022_04_08_FRAME_BUFFER_H__