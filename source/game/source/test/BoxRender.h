#ifndef __2022_03_22_BOX_RENDER_H__
#define __2022_03_22_BOX_RENDER_H__

#include "render/RenderableComponent.h"
#include "render/config.h"


USING_NAMESPACE;

class Shader;
class Mesh;

class BoxRender : public RenderableComponent
{
protected:
	Texture* m_texture;
	OGS_OLD::Shader* m_shader;
	OGS_OLD::Mesh* m_mesh;
public:
	CREATE_FUNC(BoxRender);
	BoxRender();
	virtual ~BoxRender();
	virtual void render(RenderData* render) override;
	bool init();
	virtual void onLoad() override;
};
#endif//__2022_03_22_BOX_RENDER_H__