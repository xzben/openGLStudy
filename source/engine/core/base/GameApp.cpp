#include "GameApp.h"
#include "core/base/Engine.h"
#include "core/tool/Time.h"
#include <chrono>
#include <thread>
#include "core/view/GameView.h"
#include "gfx/Device.h"

BEGIN_OGS_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(GameApp)

GameApp* GameApp::s_instance = nullptr;

GameApp::GameApp()
{
	m_gameView = new GameView;
	m_engine = new Engine();
	m_device = OGS::Gfx::createCurDevice();
	m_device->setGameView(m_gameView.get());

	GameApp::s_instance = this;
}

GameApp::~GameApp()
{

}

void GameApp::destroy()
{
	onAppExit();
	onDestroy();
}

void GameApp::exit()
{
	m_gameView->exit();
}

bool GameApp::init(const WindowCreateInfo& windowinfo)
{
	if (!m_device->init())
		return false;

	if (!m_gameView->init(windowinfo))
	{
		return false;
	}

	if (!m_engine->init())
		return false;

	onInit();
	onAppLauch();

	return true;
}
void GameApp::update(float dt)
{
	m_frameCount++;
	onUpdate(dt);
}

void GameApp::onUpdate(float dt)
{
	m_engine->update(dt);
}

void GameApp::onPreRender()
{
	m_engine->preRender();
}
 
void GameApp::onRender()
{
	m_engine->render();
}
 
void GameApp::onPostRender()
{
	m_engine->postRender();
}

void GameApp::render()
{
	onPreRender();
	onRender();
	onPostRender();
}

void GameApp::onDraw()
{
	m_engine->draw();
}

void GameApp::draw()
{
	onDraw();
}

void GameApp::run()
{
	time_t lasttime = Time::get_time_stamp_microsec();
	while (!isShoudleClose())
	{
		time_t curtime = Time::get_time_stamp_microsec();
		float offettime = (curtime - lasttime)/1000000.f;
		
		if (offettime >= m_fps)
		{
			lasttime = curtime;
			m_device->processEvent();
			update(offettime);
			render();
			draw();
			m_device->swapFrameBuffer();
		}
	}
}

bool GameApp::isShoudleClose()
{
	return m_gameView->isShoudleClose();
}


END_OGS_NAMESPACE