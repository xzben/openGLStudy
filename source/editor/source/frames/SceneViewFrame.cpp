#include "SceneViewFrame.h"
#include "core/base/Camera.h"
#include "core/components/CameraComponent.h"
#include "core/math/math.h"
#include "gfx/base/Texture.h"
#include "gfx/Device.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(SceneViewFrame)

void SceneViewFrame::renderImp()
{
	ImGui::Image((ImTextureID)m_colorTex->getHandle(), ImVec2(m_colorTex->getTextureInfo()->width, m_colorTex->getTextureInfo()->height));
}

void SceneViewFrame::handleInit()
{
	int width, height;
	OGS::Gfx::Device::getInstance()->GetScreenSize(width, height);
	OGS::Gfx::TextureInfo* colorinfo = new OGS::Gfx::TextureInfo();
	OGS::Gfx::TextureInfo* depthInfo = new OGS::Gfx::TextureInfo();
	colorinfo->width = width;
	colorinfo->height = height;
	colorinfo->usage = OGS::Gfx::TextureUsageBit::COLOR_ATTACHMENT;
	colorinfo->format = OGS::Gfx::Format::RGB8;

	depthInfo->width = width;
	depthInfo->height = height;
	depthInfo->usage = OGS::Gfx::TextureUsageBit::DEPTH_STENCIL_ATTACHMENT;
	colorinfo->format = OGS::Gfx::Format::RGB8;

	OGS::Gfx::Texture* color = OGS::Gfx::Device::getInstance()->createTexture(colorinfo);
	OGS::Gfx::Texture* depthStencil = OGS::Gfx::Device::getInstance()->createTexture(depthInfo);
	m_framebuffer = OGS::Gfx::Device::getInstance()->createFrameBuffer(color, depthStencil);
	m_colorTex = color;
}

void SceneViewFrame::handleFrameSizeChange()
{
	m_colorTex->resize(m_windowRect.width, m_windowRect.height);
}

END_EDITOR_NAMESPACE