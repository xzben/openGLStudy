#ifndef __RENDER_NODE_2021_09_07_H__
#define __RENDER_NODE_2021_09_07_H__

#include "base/Component.h"

class RenderContainor;
class Mesh;
class Shader;
class Texture;
struct SubTexture;

class RenderableComponent : public Component 
{
private:
	RenderContainor* m_containor;
public:
	RenderableComponent();
	virtual ~RenderableComponent();

	virtual void render() = 0;

	virtual void onLoad() override;
	virtual void start() override;
	virtual void onPause() override;
	virtual void onResume() override;
	virtual void stop() override;
	virtual void update(float dt) override;
	virtual void onDestroy() override;

	virtual void doDraw(Mesh* mesh, Shader* shader = nullptr, Texture* tex = nullptr, SubTexture* texs = nullptr, int subTextCount = 0);
};
#endif//__RENDER_NODE_2021_09_07_H__