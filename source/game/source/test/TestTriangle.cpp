#include "TestTriangle.h"
#include <glad/glad.h>
#include "base/Shader.h"

TestTriangle::TestTriangle() 
	: m_vao(0)
	, m_shader(nullptr)
{
	m_shader = new Shader("shader/test/test_shader");

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	float vertices[] = {
		-0.75f, 0.25f, 0.0f,
		 -0.25f, 0.25f, 0.0f,
		 -0.5f,  0.75f, 0.0f
	};

	VBO_HANDLE vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	
	glVertexAttribPointer(0, //location 0 
		3, //ÿ�����Ե�size vec3
		GL_FLOAT, //���������� float
		GL_FALSE,  // �Ƿ���Ҫ ��׼������ GL_TRUE ���ӳ�䵽 0 - 1
		3 * sizeof(float), // ÿ��Ԫ�����ڴ��еĿ縱
		(void*)0); //�������ڴ��е���ʼƫ��λ��

	// ���ö������� location 0
	glEnableVertexAttribArray(0);
}

TestTriangle::~TestTriangle() 
{
	delete m_shader;
}

void TestTriangle::render(RenderData* render)
{
	this->m_shader->use();
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}