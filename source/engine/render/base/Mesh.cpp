#include "Mesh.h"
#include <glad/glad.h>

BEGIN_NAMESPACE

const int VERTICLE_SIZE = 8;

Mesh::Mesh()
	: m_vbo(0)
	, m_vao(0)
	, m_ebo(0)
	, m_verticesCount(0)
	, m_indicesCount(0)
	, m_setuped(false)
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
}

Mesh::~Mesh()
{
	if (m_vao)
	{
		glDeleteVertexArrays(1, &m_vao);
		m_vao = 0;
	}

	if (m_vbo)
	{
		glDeleteBuffers(1, &m_vbo);
		m_vbo = 0;
	}
		
	if (m_ebo)
	{
		glDeleteBuffers(1, &m_ebo);
		m_ebo = 0;
	}	
}

void Mesh::setupGLData(float* vertices, int verticlesCount, uint* indices, int indicesCount)
{
	this->m_setuped = true;

	m_verticesCount = verticlesCount;
	m_indicesCount = indicesCount;
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, verticlesCount *sizeof(float)* VERTICLE_SIZE, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(uint), indices, GL_STATIC_DRAW);

	//指定pos 属性
	glVertexAttribPointer(SHADER_POS_INDEX, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(SHADER_POS_INDEX);

	//指定color 属性
	glVertexAttribPointer(SHADER_COLOR_INDEX, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(SHADER_COLOR_INDEX);

	//指定纹理坐标 属性
	glVertexAttribPointer(SHADER_TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(SHADER_TEXCOORD_INDEX);

	//取消buffer激活状态
	glBindVertexArray(0);
}

void Mesh::setup(float* vertices, int verticlesCount, uint* indices, int indicesCount)
{
	setupGLData(vertices, verticlesCount, indices, indicesCount);
}

void Mesh::draw()
{
	if (!this->m_setuped || this->m_verticesCount <= 0 || this->m_indicesCount <= 0) return;

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

END_NAMESPACE