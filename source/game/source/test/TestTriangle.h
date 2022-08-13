#ifndef __2022_01_04_TEST_TRIANGLE_H__
#define __2022_01_04_TEST_TRIANGLE_H__

#include "render/RenderableComponent.h"
#include "render/config.h"

class OGS_OLD::Shader;

USING_NAMESPACE;

class TestTriangle : public RenderableComponent
{
protected:
	VAO_HANDLE m_vao;
	OGS_OLD::Shader* m_shader;
public:
	TestTriangle();
	virtual ~TestTriangle();
	virtual void render(RenderData* render) override;
};
#endif//__2022_01_04_TEST_TRIANGLE_H__