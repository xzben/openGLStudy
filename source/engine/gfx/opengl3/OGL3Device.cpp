#include "OGL3Device.h"
#include "glfw/glfw3.h"
#include "core/view/GameView.h"
#include "gfx/opengl3/GL3Buffer.h"
#include "gfx/opengl3/states/GL3Sampler.h"
#include "gfx/opengl3/GL3Texture.h"
#include "gfx/opengl3/GL3FrameBuffer.h"
#include "gfx/opengl3/GL3Shader.h"
#include "gfx/opengl3/GL3InputAssembler.h"

BEGIN_OGS_GFX_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(OGL3Device)

static void glfw_error_callback(int error, const char* description)
{
	CCLOG_ERROR("Glfw Error %d: %s\n", error, description);
}

bool OGL3Device::init()
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return false;

	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	return true;
}

void OGL3Device::processEvent()
{
	glfwPollEvents();
}

void OGL3Device::swapFrameBuffer()
{
	glfwSwapBuffers(m_gameview->GetWindow());
}

void OGL3Device::GetScreenSize(int& width, int& height)
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	width = mode->width;
	height = mode->height;
}

CommandBuffer* OGL3Device::createCommandBuffer(Queue* queue, CommandBufferType type)
{
	return nullptr;
}
Swapchain* OGL3Device::createSwapchain(SwapchainInfo* info) 
{
	return nullptr;
}
Buffer* OGL3Device::createBuffer(BufferInfo* info)
{
	GL3Buffer* buffer = GL3Buffer::create();
	buffer->initialize(*info);
	return buffer;
}
Texture* OGL3Device::createTexture(TextureInfo* info)
{
	auto tex = GL3Texture::create();
	tex->initialize(info);
	return tex;
}
DescriptorSet* OGL3Device::createDescriptSet(DescriptorSetLayout* layout)
{
	return nullptr;
}
Shader* OGL3Device::createShader(ShaderInfo* info)
{
	Shader* shader = new GL3Shader();
	shader->initilize(info);
	return shader;
}
InputAssembler* OGL3Device::createInputAssembler(InputAssemblerInfo* info)
{
	InputAssembler* input = new GL3InputAssembler();
	input->initialize(*info);
	return input;
}

RenderPass* OGL3Device::createRenderPass(RenderPassInfo* info)
{
	return nullptr;
}

FrameBuffer* OGL3Device::createFrameBuffer(FrameBufferInfo* info)
{
	FrameBuffer* buffer = new GL3FrameBuffer();
	buffer->initilize(*info);
	return buffer;
}

FrameBuffer* OGL3Device::createFrameBuffer(Texture* color, Texture* depthStencil)
{
	FrameBuffer* buffer = new GL3FrameBuffer();
	buffer->initilize(color, depthStencil);
	return buffer;
}

DescriptSetLayout* OGL3Device::createDescriptSetLayout(DescriptorSetLayoutInfo* info)
{
	return nullptr;
}
PipelineLayout* OGL3Device::createPipelineLayout(PipelineLayoutInfo* info)
{
	return nullptr;
}
PipelineState* OGL3Device::createPipelineState(PipelineStateInfo* info)
{
	return nullptr;
}
Queue* OGL3Device::createQueue(QueueType type)
{
	return nullptr;
}

AutoRef<Sampler> OGL3Device::getSampler(SamplerInfo* info) 
{
	HASH_CODE hash = Sampler::computeHash(info);
	auto sampler = getSamplerByHash(hash);
	if (sampler)
	{
		return sampler;
	}
	else
	{
		return addSampler(hash, new GL3Sampler(info, hash ));
	}
}

const std::vector<AutoRef<Swapchain>>& OGL3Device::getSwapchains()
{
	return m_swapchains;
}

GeneralBarrier* OGL3Device::getGeneralBarrier(GeneralBarrierInfo* info)
{
	return nullptr;
}
TextureBarrier* OGL3Device::getTextureBarrier(TextureBarrierInfo* info)
{
	return nullptr;
}
BufferBarrier* OGL3Device::getBufferBarrier(BufferBarrierInfo* info)
{
	return nullptr;
}
END_OGS_GFX_NAMESPACE