#include "TestRect.h"
#include <glad/glad.h>
#include "base/Shader.h"

TestRect::TestRect()
	: m_vao(0)
	, m_shader(nullptr)
{
	m_shader = new Shader("test/uniform_color.vs", "test/uniform_color.fs");

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	float vertices[] = {
		// ��һ��������
		0.25f, 0.25f, 0.0f,
		0.75f, 0.25f, 0.0f,
		0.75f, 0.75f, 0.0f,
		0.25f, 0.75f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	VBO_HANDLE vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	EBO_HANDLE ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, //location 0 
		3, //ÿ�����Ե�size vec3
		GL_FLOAT, //���������� float
		GL_FALSE,  // �Ƿ���Ҫ ��׼������ GL_TRUE ���ӳ�䵽 0 - 1
		3 * sizeof(float), // ÿ��Ԫ�����ڴ��еĿ縱
		(void*)0); //�������ڴ��е���ʼƫ��λ��

	// ���ö������� location 0
	glEnableVertexAttribArray(0);
}

TestRect::~TestRect()
{
	delete m_shader;
}

void TestRect::render()
{
	this->m_shader->use();
	m_shader->setVec4("ourColor", fVec4(1.0f, 0.f, 0.f, 0.f));
	//m_shader->setFloat("time", this->getLastDt());

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}