#include "RenderableComponent.h"
#include "base/SceneManager.h"
#include "render/RenderContainor.h"
#include "base/Scene.h"

RenderableComponent::RenderableComponent()
	: m_containor(nullptr)
{

}

RenderableComponent::~RenderableComponent()
{
	
}

void RenderableComponent::onLoad()
{

}

void RenderableComponent::start() 
{
	Component::start();
	this->m_containor = SceneManager::getInstance()->getCurScene();
	if (this->m_containor) {
		this->m_containor->addRenderComp(this);
	}
}

void RenderableComponent::onPause() 
{

}

void RenderableComponent::onResume() 
{

}

void RenderableComponent::stop() 
{
	Component::stop();
	if (m_containor) {
		m_containor->removeRenderComp(this);
	}
}

void RenderableComponent::update(float dt) 
{

}

void RenderableComponent::onDestroy() 
{

}