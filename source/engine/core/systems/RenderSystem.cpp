#include "RenderSystem.h"
#include "core/components/CameraComponent.h"
#include "core/base/Scene.h"
#include "core/base/GameApp.h"
#include "core/view/Screen.h"
#include "gfx/Device.h"
#include <algorithm>

BEGIN_OGS_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(RenderSystem)

RenderSystem* RenderSystem::s_instance = nullptr;

RenderSystem* RenderSystem::getInstance()
{
	return s_instance;
}

RenderSystem::RenderSystem()
{
	m_name = "RenderSystem";
	s_instance = this;
	//m_defaultRenderWindow = RenderWindow::create();
}

void RenderSystem::handleInit()
{
	m_divice = GameApp::getApp()->getDevice();
}

void RenderSystem::setRenderScene(Scene* scene)
{
	if (m_curScene)
	{
		m_curScene->doStop();
	}
	m_curScene = scene;
	if (m_curScene)
	{
		m_curScene->doStart();
	}
}

void RenderSystem::update(float dt)
{
	render();
}

void RenderSystem::destroy()
{

}

void RenderSystem::preRender()
{

}

void RenderSystem::render()
{
	
}

void RenderSystem::draw()
{
	std::vector<Renderable*> renders;
	for (CameraComponent* cam : m_cameras)
	{
		if (cam->isEnable())
		{
			cam->render(renders);
		}
	}
}

void RenderSystem::postRender()
{

}

void RenderSystem::addCamera(CameraComponent* camera)
{
	m_cameras.push_back(camera);
	std::sort(m_cameras.begin(), m_cameras.end(), [](CameraComponent* a, CameraComponent* b) {
		return a->getPriority() < b->getPriority();
	});
}

void RenderSystem::removeCamera(CameraComponent* camera)
{
	for (auto it = m_cameras.begin(); it != m_cameras.end(); it++)
	{
		if (*it == camera)
		{
			it = m_cameras.erase(it);
			break;
		}
	}
}

void RenderSystem::addRenderWindow(RenderWindow* window)
{
	m_renderwindows.push_back(window);
}

void RenderSystem::removeRenderWindow(RenderWindow* window)
{
	for (auto it = m_renderwindows.begin(); it != m_renderwindows.end(); it++)
	{
		if (*it == window)
		{
			it = m_renderwindows.erase(it);
			break;
		}
	}
}

void RenderSystem::updateEngineContentViewport(const Rect& viewport)
{
	Screen::setViewport(viewport);
}

void RenderSystem::addRenderable(Renderable* obj)
{
	m_renders.push_back(obj);
}

void RenderSystem::removeRenderable(Renderable* obj)
{
	for (auto it = m_renders.begin(); it != m_renders.end(); it++)
	{
		if (*it == obj)
		{
			it = m_renders.erase(it);
			break;
		}
	}
}
END_OGS_NAMESPACE