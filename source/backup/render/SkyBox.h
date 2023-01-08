#ifndef __2022_04_11_SKYBOX_H__
#define __2022_04_11_SKYBOX_H__
#include "common.h"
#include "render/RenderableComponent.h"
#include "base/Object.h"

BEGIN_NAMESPACE

class Mesh;
class Material;

class SkyBox : public RenderableComponent
{
protected:
	Mesh* m_mesh;
	Material* m_material;
public:
	SkyBox();
	virtual ~SkyBox();

	bool init(std::string faces[6]);

	virtual void render(RenderData* render);
};

END_NAMESPACE
#endif//__2022_04_11_SKYBOX_H__