#ifndef __2022_03_22_BOX_RENDER_H__
#define __2022_03_22_BOX_RENDER_H__

#include "render/RenderableComponent.h"
#include "render/config.h"

class OGS::Shader;
class OGS::Mesh;

USING_NAMESPACE;

class BoxRender : public RenderableComponent
{
protected:
	Texture* m_texture;
	Shader* m_shader;
	Mesh* m_mesh;
public:
	BoxRender();
	virtual ~BoxRender();
	virtual void render() override;
	bool init();
};
#endif//__2022_03_22_BOX_RENDER_H__