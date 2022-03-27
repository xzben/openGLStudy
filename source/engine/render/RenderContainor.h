#ifndef __2022_03_07_RENDER_CONTAINOR_H__
#define __2022_03_07_RENDER_CONTAINOR_H__

#include "common.h"
#include "math/Mat4.h"
#include "render/RenderData.h"
BEGIN_NAMESPACE

class RenderableComponent;

class RenderContainor
{
protected:
	std::vector<RenderableComponent*> m_renderComps;
public:
	virtual void render(RenderData* render);
	void addRenderComp(RenderableComponent* com);
	void removeRenderComp(RenderableComponent* com);
};

END_NAMESPACE

#endif//__2022_03_07_RENDER_CONTAINOR_H__