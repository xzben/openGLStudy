#ifndef __2022_01_04_TEST_TRIANGLE_H__
#define __2022_01_04_TEST_TRIANGLE_H__

#include "render/RenderableComponent.h"
#include "render/config.h"


class Shader;

class TestTriangle : public RenderableComponent
{
protected:
	VAO_HANDLE m_vao;
	Shader* m_shader;
public:
	TestTriangle();
	virtual ~TestTriangle();
	virtual void render() override;
};
#endif//__2022_01_04_TEST_TRIANGLE_H__