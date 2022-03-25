#include "base/Application.h"
#include "base/SceneManager.h"
#include "event/EventDispatcher.h"
#include <GLFW/glfw3.h>
#include <iostream>

BEGIN_NAMESPACE

Application* Application::s_instance = nullptr;

Application::Application() 
{
	this->m_offsetCount = 0.0f;
	this->m_lastDt = 0.0f;
	this->setFPS(60);

	this->m_resolutionSize.height = 0.f;
	this->m_resolutionSize.width = 0.f;

	this->m_dispatcher = new EventDispatcher();
	CC_ASSERT(s_instance == nullptr);
	s_instance = this;
}

Application::~Application() {
	s_instance = nullptr;
}

Application* Application::getInstance() {
	CC_ASSERT(s_instance != nullptr);
	return s_instance;
}

bool Application::shiftTime(float offsettime) 
{
	this->m_offsetCount += offsettime;
	
	if (this->m_offsetCount >= this->m_fps)
	{
		this->m_lastDt = this->m_offsetCount;
		this->m_offsetCount = 0.0f;
		this->m_timer.x = this->m_lastDt;
		this->m_timer.y += this->m_lastDt;
		return true;
	}

	return false;
}

bool Application::update() 
{
	float dt = this->m_lastDt;

	SceneManager::getInstance()->update(dt);
	return false;
}

void Application::render()
{
	SceneManager::getInstance()->render();
}

void Application::setFPS(int fps) 
{
	m_fps = 1.0f / fps;
}

void Application::setFrameSize(const Size & frameSize)
{
	this->setFrameSize(frameSize.width, frameSize.height);
}

void Application::setFrameSize(const float& width, const float& height)
{
	this->m_frameSize.width = width;
	this->m_frameSize.height = height;

	if (this->m_resolutionSize.width == 0 || this->m_resolutionSize.height == 0)
	{
		this->setDesignResolution(width, height);
	}
}

void Application::setDesignResolution(float width, float height, ResolutionFit fit /*= ResolutionFit::AUTO_FIT*/)
{
	this->m_resolutionSize.width = width;
	this->m_resolutionSize.height = height;
	this->m_fitway = fit;
}

const Size& Application::getFrameSize()
{
	return this->m_frameSize;
}

const Size& Application::getResolutionSize()
{
	return this->m_resolutionSize;
}

void Application::updateDrawSize()
{
	float scalef = this->m_frameSize.width / this->m_frameSize.height;
	float scaled = this->m_resolutionSize.width / this->m_resolutionSize.height;

	float scalex = this->m_frameSize.width / this->m_resolutionSize.width;
	float scaley = this->m_frameSize.height / this->m_resolutionSize.height;

	ResolutionFit way = this->m_fitway;

	if (way == ResolutionFit::AUTO_FIT) {
		if (scaled > scalef) {
			way = ResolutionFit::FIXED_HEIGHT;
		}
		else {
			way = ResolutionFit::FIXED_WIDTH;
		}
	}

	switch (way)
	{
	case ResolutionFit::FIXED_WIDTH:
	{
		this->m_drawSize.width = this->m_resolutionSize.width;
		this->m_drawSize.height = this->m_drawSize.width / scalef;
		break;
	}
	case ResolutionFit::FIXED_HEIGHT:
	{
		this->m_drawSize.height = this->m_resolutionSize.height;
		this->m_drawSize.width = this->m_drawSize.height * scalef;
		break;
	}
	}
}


void Application::dispatchKeyboard(int key, bool press)
{
	EventKeyboard evt(key);
	this->m_dispatcher->dispatchKeyboard(&evt);
}

void Application::dispatchTouch(TouchStatus status, float x, float y)
{
	EventTouch evt(status, fVec2(x, y));
	evt.prePos = m_preTouchPos;

	m_preTouchPos = fVec2(x, y);
	this->m_dispatcher->dispatchTouch(&evt);
}

void Application::dispatchMouse(int key, bool press)
{
	EventMouse evt(key, press);

	this->m_dispatcher->dispatchMouse(&evt);
}

Camera* Application::getMainCamera()
{
	if (m_mainCamera == nullptr)
	{
		m_mainCamera = Camera::createDefault(true);
	}

	return m_mainCamera;
}

END_NAMESPACE