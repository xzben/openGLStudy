#pragma once

#include "GfxObject.h"
#include "core/math/math.h"

BEGIN_OGS_GFX_NAMESPACE
class GfxQueue;
class RenderPass;
class FrameBuffer;

class CommandBuffer : public GfxObject
{
	DECLARE_RUNTIME_CLASS(CommandBuffer)
public:
	CommandBuffer() :GfxObject(ObjectType::COMMAND_BUFFER) {}
	virtual ~CommandBuffer() {}
	void begin(RenderPass* renderPass, uint32 subpass, FrameBuffer* framebuffer);
	void end();

	void beginRenderPass(RenderPass* renderPass, FrameBuffer* frameBuffer, const OGS::Rect& reanderArea, OGS::Color& clearColor, uint8 clearDepth, uint8 clearStencil);
	void endRenderPass();

protected:
	CommandBufferType m_type{ CommandBufferType::PRIMARY };
	AutoRef<GfxQueue> m_queue;
	uint32			  m_numDrawCalls;
	uint32			  m_numInstances;
	uint32			  m_numTris;
};
END_OGS_GFX_NAMESPACE