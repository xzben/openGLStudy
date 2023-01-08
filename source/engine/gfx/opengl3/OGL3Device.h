#pragma once

#include "gfx/Device.h"

BEGIN_OGS_GFX_NAMESPACE
class OGL3Device : public Device
{
	DECLARE_RUNTIME_CLASS(OGL3Device)
public:
	virtual bool init() override;
	virtual void processEvent() override;
	virtual void swapFrameBuffer()override;
	virtual void GetScreenSize(int& width, int& height) override;

	virtual CommandBuffer* createCommandBuffer(Queue* queue, CommandBufferType type) override;
	virtual Swapchain* createSwapchain(SwapchainInfo* info) override;
	virtual Buffer* createBuffer(BufferInfo* info) override;
	virtual Texture* createTexture(TextureInfo* info) override;
	virtual DescriptorSet* createDescriptSet(DescriptorSetLayout* layout)override;
	virtual Shader* createShader(ShaderInfo* info)override;
	virtual InputAssembler* createInputAssembler(InputAssemblerInfo* info)override;
	virtual RenderPass* createRenderPass(RenderPassInfo* info)override;
	virtual FrameBuffer* createFrameBuffer(FrameBufferInfo* info)override;
	virtual DescriptSetLayout* createDescriptSetLayout(DescriptorSetLayoutInfo* info)override;
	virtual PipelineLayout* createPipelineLayout(PipelineLayoutInfo* info)override;
	virtual PipelineState* createPipelineState(PipelineStateInfo* info)override;
	virtual Queue* createQueue(QueueType type)override;
	virtual AutoRef<Sampler> getSampler(SamplerInfo* info)override;
	virtual const std::vector<AutoRef<Swapchain>>& getSwapchains()override;
	virtual GeneralBarrier* getGeneralBarrier(GeneralBarrierInfo* info)override;
	virtual TextureBarrier* getTextureBarrier(TextureBarrierInfo* info)override;
	virtual BufferBarrier* getBufferBarrier(BufferBarrierInfo* info)override;
};

END_OGS_GFX_NAMESPACE