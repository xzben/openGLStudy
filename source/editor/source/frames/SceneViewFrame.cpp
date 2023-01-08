#include "SceneViewFrame.h"
#include "core/base/Camera.h"
#include "core/components/CameraComponent.h"
#include "core/math/math.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(SceneViewFrame)

void SceneViewFrame::renderImp()
{
	/*if (m_renderWindow->begin())
	{
		m_editorCamera->getCameraCom()->clear();
	}
	m_renderWindow->end();
	WeakRef<OGS::Texture> rendertarget = m_renderWindow->getRenderTarget();
	if (rendertarget)
	{
		ImGui::Image((ImTextureID)rendertarget->getHandle(), ImVec2(m_windowRect.width, m_windowRect.height));
	}*/
}

void SceneViewFrame::handleInit()
{
	//m_editorCamera = OGS::Camera::createDefault3DCamera();
	//m_renderWindow = OGS::RenderWindow::create();
	//m_renderWindow->setViewport(m_windowRect);
	//m_editorCamera->getCameraCom()->setRenderWindow(m_renderWindow.get());
}

void SceneViewFrame::handleFrameSizeChange()
{
	//m_renderWindow->setViewport(m_windowRect);
}

END_EDITOR_NAMESPACE