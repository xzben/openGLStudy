#ifndef __2022_03_07_RENDER_CONTAINOR_H__
#define __2022_03_07_RENDER_CONTAINOR_H__

#include "common.h"
#include "math/Mat4.h"

BEGIN_NAMESPACE

class RenderableComponent;
class Camera;

class RenderContainor
{
protected:
	std::vector<RenderableComponent*> m_renderComps;
public:
	virtual void render(Camera* cam);
	void addRenderComp(RenderableComponent* com);
	void removeRenderComp(RenderableComponent* com);
};

END_NAMESPACE

#endif//__2022_03_07_RENDER_CONTAINOR_H__