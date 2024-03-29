#ifndef __RENDER_NODE_2021_09_07_H__
#define __RENDER_NODE_2021_09_07_H__

#include "base/Component.h"
#include "render/RenderData.h"
BEGIN_NAMESPACE

class RenderContainor;
class Mesh;
class Shader;
class Texture;
class Camera;
struct SubTexture;
class Material;

class RenderableComponent : public Component 
{
protected:
	RenderContainor* m_containor;
public:
	RenderableComponent();
	virtual ~RenderableComponent();

	virtual void render(RenderData* render) = 0;
	virtual void onLoad() override;
	virtual void start() override;
	virtual void onPause() override;
	virtual void onResume() override;
	virtual void stop() override;
	virtual void update(float dt) override;
	virtual void onDestroy() override;

	virtual void doDraw(RenderData* render, Mesh* mesh, Shader* shader = nullptr, Texture* tex = nullptr, SubTexture* texs = nullptr, int subTextCount = 0);
	virtual void doDraw(RenderData* render, Mesh* mesh, Material* material);
};

END_NAMESPACE
#endif//__RENDER_NODE_2021_09_07_H__