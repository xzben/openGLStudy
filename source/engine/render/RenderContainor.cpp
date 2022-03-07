#include "RenderContainor.h"
#include "RenderableComponent.h"

void RenderContainor::addRenderComp(RenderableComponent* com)
{
	this->m_renderComps.push_back(com);
}

void RenderContainor::removeRenderComp(RenderableComponent* com)
{
	for (auto it = m_renderComps.begin(); it != this->m_renderComps.end(); it++)
	{
		if (com == *it) {
			this->m_renderComps.erase(it);
			break;
		}
	}
}

void RenderContainor::render()
{
	for (auto it = m_renderComps.begin(); it != m_renderComps.end(); it++)
	{
		(*it)->render();
	}
}