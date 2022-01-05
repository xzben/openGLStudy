#include "base/Application.h"
#include "base/SceneManager.h"
#include <GLFW/glfw3.h>
#include <iostream>

Application* Application::s_instance = nullptr;

Application::Application() 
{
	this->m_offsetCount = 0.0f;
	this->m_lastDt = 0.0f;
	this->setFPS(60);
	CC_ASSET(s_instance == nullptr);
	s_instance = this;
}

Application::~Application() {
	s_instance = nullptr;
}

Application* Application::getInstance() {
	CC_ASSET(s_instance != nullptr);
	return s_instance;
}

bool Application::update(float offsettime) 
{
	this->m_offsetCount += offsettime;
	if (this->m_offsetCount >= this->m_fps) 
	{
		this->m_lastDt = this->m_offsetCount;
		this->m_offsetCount = 0.0f;

		return true;
	}

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