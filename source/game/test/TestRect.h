#ifndef __2022_01_05_TEST_RECT_H__
#define __2022_01_05_TEST_RECT_H__

#include "render/RenderableComponent.h"
#include "render/config.h"

class OGS::Shader;

USING_NAMESPACE;

class TestRect : public RenderableComponent
{
protected:
	VAO_HANDLE m_vao;
	Shader* m_shader;
public:
	TestRect();
	virtual ~TestRect();
	virtual void render(RenderData* render) override;
};
#endif//__2022_01_05_TEST_RECT_H__