#include "GameViewFrame.h"
#include "core/systems/RenderSystem.h"
BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(GameViewFrame)

void GameViewFrame::handleInit()
{

}

void GameViewFrame::renderImp()
{
	OGS::RenderSystem::getInstance()->preRender();
	OGS::RenderSystem::getInstance()->render();
	OGS::RenderSystem::getInstance()->postRender();
	OGS::RenderSystem::getInstance()->draw();

	/*WeakRef<OGS::Texture> rendertarget = OGS::RenderSystem::getInstance()->getDefaultRenderWindow()->getRenderTarget();
	if (rendertarget)
	{
		ImGui::Image((ImTextureID)rendertarget->getHandle(), ImVec2(m_windowRect.width, m_windowRect.height));
	}*/
}

void GameViewFrame::handleFrameSizeChange()
{
	OGS::RenderSystem::getInstance()->updateEngineContentViewport(m_windowRect);
}

END_EDITOR_NAMESPACE