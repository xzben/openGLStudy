#pragma once

#include "GfxObject.h"

BEGIN_OGS_GFX_NAMESPACE
class ColorAttachment;
class DepthStencilAttachment;
class GeneralBarrier;
class BufferBarrier;
class Buffer;
class TextureBarrier;
class Texture;

class SubpassDependency : public Object
{
public:
	uint32 srcSubpass;
	uint32 dstSubpass;
	AutoRef<GeneralBarrier> generalBarrier;
	AutoRef<BufferBarrier>  bufferBarrier;
	AutoRef<Buffer>	buffer;
	uint32 bufferBarrierCount;
	AutoRef<TextureBarrier> textureBarriers;
	AutoRef<Texture> texture;
	uint32 textureBarrierCount;

};
class RenderPassInfo
{
public:
	std::vector<AutoRef<ColorAttachment>> colorAttachments;
	AutoRef<DepthStencilAttachment> depthStencilAttachment;
	std::vector<AutoRef<SubpassInfo>> subpasses;
	std::vector<AutoRef<SubpassDependency>> dependencies;
};

class RenderPass : public GfxObject
{
	DECLARE_RUNTIME_CLASS(RenderPass)
public:
	RenderPass() :GfxObject(ObjectType::RENDER_PASS) {}
	virtual ~RenderPass(){}
protected:
	std::vector<AutoRef<ColorAttachment>> m_colorInfos;
	AutoRef<DepthStencilAttachment>		  m_detphStencilInfo;
	std::vector<AutoRef<SubpassInfo>>     m_subpasses;
	HASH_CODE							  m_hash;
};
END_OGS_GFX_NAMESPACE