#include "SceneManager.h"
#include "base/Scene.h"
#include "base/Node.h"
#include "render/RenderableComponent.h"

SceneManager* SceneManager::s_instance = nullptr;

SceneManager* SceneManager::getInstance() {
	if (s_instance == nullptr) {
		s_instance = new SceneManager();
	}

	return s_instance;
}

SceneManager::SceneManager() 
	: m_scene(nullptr)
{

}

SceneManager::~SceneManager() 
{

}

void SceneManager::addRenderComp(RenderableComponent* com)
{
	this->m_renderComps.push_back(com);
}

void SceneManager::removeRenderComp(RenderableComponent* com)
{
	for (auto it = m_renderComps.begin(); it != this->m_renderComps.end(); it++)
	{
		if (com == *it) {
			this->m_renderComps.erase(it);
			break;
		}
	}
}

void SceneManager::changeScene(Scene* scene) 
{
	if (scene == nullptr) return;

	if (this->m_scene != nullptr) {
		delete this->m_scene;
		this->m_scene = nullptr;
	}

	this->m_scene = scene;
	scene->doStart();
	scene->doResume();
}

Scene* SceneManager::getCurScene()
{
	return m_scene;
}

void SceneManager::render()
{
	for (auto it = m_renderComps.begin(); it != m_renderComps.end(); it++)
	{
		(*it)->render();
	}
}