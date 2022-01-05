#include "RenderableComponent.h"
#include "base/SceneManager.h"

RenderableComponent::RenderableComponent()
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
	SceneManager::getInstance()->addRenderComp(this);
}

void RenderableComponent::onPause() 
{

}

void RenderableComponent::onResume() 
{

}

void RenderableComponent::stop() 
{
	Component::start();
	SceneManager::getInstance()->removeRenderComp(this);
}

void RenderableComponent::update(float dt) 
{

}

void RenderableComponent::onDestroy() 
{

}