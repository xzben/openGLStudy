#include "SceneManager.h"
#include "base/Scene.h"
#include "base/Node.h"
#include "render/RenderableComponent.h"

BEGIN_NAMESPACE

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

void SceneManager::update(float dt)
{
	if (this->m_scene) {
		this->m_scene->doUpdate(dt);
	}
}

void SceneManager::render()
{
	RenderContainor::render();
	if (this->m_scene)
	{
		const fMat4& identity = MathUtil::IdentityMat4();
		this->m_scene->updateWorlModelMat(identity, false);
		this->m_scene->render();
	}
		
}

END_NAMESPACE