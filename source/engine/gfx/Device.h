#pragma once

#include "common.h"
#include "core/math/math.h"
#include "gfx/base/GfxObject.h"
#include "gfx/base/Attachment.h"
#include "gfx/base/Attribute.h"
#include "gfx/base/DescriptorSet.h"
#include "gfx/base/DescriptorSetLayout.h"
#include "gfx/base/DescriptorSetLayoutBinding.h"
#include "gfx/base/Buffer.h"
#include "gfx/base/CommandBuffer.h"
#include "gfx/base/InputAssembler.h"
#include "gfx/base/FrameBuffer.h"
#include "gfx/base/Queue.h"
#include "gfx/base/RenderPass.h"
#include "gfx/base/Shader.h"
#include "gfx/base/Swapchain.h"
#include "gfx/base/Texture.h"
#include "gfx/base/PipelineLayout.h"
#include "gfx/base/Uniform.h"
#include "gfx/base/states/buffer_barrier.h"
#include "gfx/base/states/general_barrier.h"
#include "gfx/base/states/sampler.h"
#include "gfx/base/states/texture_barrier.h"
#include "gfx/base/PipelineState.h"

namespace OGS {
	class GameView;
};

BEGIN_OGS_GFX_NAMESPACE

class Device : public Object
{
	DECLARE_RUNTIME_CLASS(Device)
	static Device* s_instance;
public:
	static Device* getInstance();
	Device();
	virtual bool init() { return true; }
	virtual void processEvent(){}
	virtual void swapFrameBuffer() {}
	virtual void clear(Color color) {}
	virtual void GetScreenSize(int& width, int& height) { width = 0; height = 0; };
	virtual void setGameView(GameView* gameview);

	void acquire(const std::vector<Swapchain>& swapchains){}
	void present(){}
	void flushCommands(const std::vector<CommandBuffer>& cmdBuffs){}
	virtual CommandBuffer* createCommandBuffer(Queue* queue, CommandBufferType type) { return nullptr; }
	virtual Swapchain* createSwapchain(SwapchainInfo* info) { return nullptr; }
	virtual Buffer* createBuffer(BufferInfo* info) { return nullptr; }
	virtual Texture* createTexture(TextureInfo* info) { return nullptr; }
	virtual DescriptorSet* createDescriptSet(DescriptorSetLayout* layout) { return nullptr; }
	virtual Shader* createShader(ShaderInfo* info) { return nullptr; }
	virtual InputAssembler* createInputAssembler(InputAssemblerInfo* info) { return nullptr; }
	virtual RenderPass* createRenderPass(RenderPassInfo* info) { return nullptr; }
	virtual FrameBuffer* createFrameBuffer(FrameBufferInfo* info) { return nullptr; }
	virtual FrameBuffer* createFrameBuffer(Texture* color, Texture* depthStencil) { return nullptr; }
	virtual DescriptSetLayout* createDescriptSetLayout(DescriptorSetLayoutInfo* info) { return nullptr; }
	virtual PipelineLayout* createPipelineLayout(PipelineLayoutInfo* info) { return nullptr; }
	virtual PipelineState* createPipelineState(PipelineStateInfo* info) { return nullptr; }
	virtual Queue* createQueue(QueueType type) { return nullptr; }
	virtual AutoRef<Sampler> getSampler(SamplerInfo* info) { return nullptr; }
	virtual const std::vector<AutoRef<Swapchain>>& getSwapchains() { return std::vector<AutoRef<Swapchain>>(); }
	virtual GeneralBarrier* getGeneralBarrier(GeneralBarrierInfo* info) { return nullptr; }
	virtual TextureBarrier* getTextureBarrier(TextureBarrierInfo* info) { return nullptr; }
	virtual BufferBarrier* getBufferBarrier(BufferBarrierInfo* info) { return nullptr; }

	virtual void copyBuffersToTexture() {};
	virtual void copyTextureToBuffers() {};
	virtual void copyTexImagesToTexture() {};
	bool hasFeature(Feature feature) { return false; }
	FormatFeatureBit getFormatFeatures(Format format) { return FormatFeatureBit::NONE; }
protected:
	AutoRef<Sampler> getSamplerByHash(HASH_CODE hash);
	Sampler* addSampler(HASH_CODE hash, Sampler* sampler);
protected:
	AutoRef<GameView> m_gameview;
	API m_gfxApi{ API::UNKNOWN };
	std::string m_renderer{""};
	std::string m_vendor{""};
	bool m_features[Feature::COUNT];
	FormatFeatureBit m_formatFeatures[Feature::COUNT];
	AutoRef<Gfx::Queue> m_queue;
	AutoRef<CommandBuffer> m_cmdBuff;
	std::vector<AutoRef<Swapchain>> m_swapchains;
	uint32       m_numDrawCalls;
	uint32       m_numInstances;
	uint32		 m_numTris;
	MemoryStatus m_memoryStatus;
	DeviceCaps   m_caps;
	BindingMappingInfo m_bindingMappingInfo;
	std::unordered_map<HASH_CODE, AutoRef<Sampler>> m_samplers;
	std::unordered_map<int32, AutoRef<GeneralBarrier>> m_generalBarries;
	std::unordered_map<int32, AutoRef<TextureBarrier>> m_textureBarries;
	std::unordered_map<int32, AutoRef<BufferBarrier>> m_bufferBarries;
};

Device* createCurDevice();
END_OGS_GFX_NAMESPACE