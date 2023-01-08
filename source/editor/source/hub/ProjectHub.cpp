#include "ProjectHub.h"
#include "core/view/GameView.h"
#include "gfx/Device.h"
#include "HubWindow.h"

USING_OGS_NAMESPACE;

BEGIN_EDITOR_NAMESPACE


ProjectHub::ProjectHub()
{

}

void ProjectHub::init()
{
	m_device = Gfx::createCurDevice();
	m_device->init();

	WindowCreateInfo info;
	info.maximized = false;
	info.is_fullscreen = false;
	info.title = "OpenGLStudy Hub";
	info.width = 1000;
	info.height = 580;
	m_gameview = new GameView();
	m_gameview->init(info);
	
	m_device->setGameView(m_gameview.get());

	int sw, sh;
	m_device->GetScreenSize(sw, sh);
	m_gameview->setPosition(sw / 2 - info.width/2, sh / 2 - info.height/2);

	m_hubwindow = new HubWindow(m_gameview.get());

	m_hubwindow->init();
}

void ProjectHub::render()
{
	m_hubwindow->render();
}

void ProjectHub::draw()
{
	m_hubwindow->draw();
}

std::tuple<bool, GameProject*> ProjectHub::run()
{
	while (!m_gameview->isShoudleClose())
	{
		m_device->processEvent();
		render();
		draw();
		m_device->swapFrameBuffer();
	}

	return { m_ready, m_openProject.get() };
}

END_EDITOR_NAMESPACE