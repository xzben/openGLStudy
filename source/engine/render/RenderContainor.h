#ifndef __2022_03_07_RENDER_CONTAINOR_H__
#define __2022_03_07_RENDER_CONTAINOR_H__

#include "common.h"
class RenderableComponent;

class RenderContainor
{
protected:
	std::vector<RenderableComponent*> m_renderComps;
public:
	virtual void render();
	void addRenderComp(RenderableComponent* com);
	void removeRenderComp(RenderableComponent* com);
};
#endif//__2022_03_07_RENDER_CONTAINOR_H__