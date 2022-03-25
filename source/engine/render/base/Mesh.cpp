#include "Mesh.h"
#include <glad/glad.h>

BEGIN_NAMESPACE

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

static int getVerticleItemCount(VerticleMember vmembers)
{
	int verticleCount = 0;

	if ((uint(vmembers) & (uint)VerticleMember::POS))
	{
		verticleCount += 3;
	}

	if ((uint(vmembers) & (uint)VerticleMember::COLOR))
	{
		verticleCount += 3;
	}

	if ((uint(vmembers) & (uint)VerticleMember::TEXCOORD))
	{
		verticleCount += 2;
	}

	if ((uint(vmembers) & (uint)VerticleMember::NORMAL))
	{
		verticleCount += 3;
	}

	return verticleCount;
}

void Mesh::setupGLData(float* vertices, int verticlesCount, uint* indices, int indicesCount, VerticleMember vmembers)
{
	this->m_setuped = true;

	m_verticesCount = verticlesCount;
	m_indicesCount = indicesCount;
	glBindVertexArray(m_vao);

	int verticleItemCount = getVerticleItemCount(vmembers);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, verticlesCount *sizeof(float)* verticleItemCount, vertices, GL_STATIC_DRAW);

	if (indicesCount > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(uint), indices, GL_STATIC_DRAW);
	}

	
	int offset = 0;
	if ((uint(vmembers) & (uint)VerticleMember::POS))
	{
		//指定pos 属性
		glVertexAttribPointer(SHADER_POS_INDEX, 3, GL_FLOAT, GL_FALSE, verticleItemCount * sizeof(float), (void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(SHADER_POS_INDEX);
		offset += 3;
	}

	
	if ((uint(vmembers) & (uint)VerticleMember::COLOR))
	{
		//指定color 属性
		glVertexAttribPointer(SHADER_COLOR_INDEX, 3, GL_FLOAT, GL_FALSE, verticleItemCount * sizeof(float), (void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);
		offset += 3;
	}

	if ((uint(vmembers) & (uint)VerticleMember::TEXCOORD))
	{
		//指定纹理坐标 属性
		glVertexAttribPointer(SHADER_TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE, verticleItemCount * sizeof(float), (void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(SHADER_TEXCOORD_INDEX);
		offset += 2;
	}

	if ((uint(vmembers) & (uint)VerticleMember::NORMAL))
	{
		//指定法向量 属性
		glVertexAttribPointer(SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, verticleItemCount * sizeof(float), (void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(SHADER_NORMAL_INDEX);
		offset += 3;
	}

	//取消buffer激活状态
	glBindVertexArray(0);
}

void Mesh::setup(float* vertices, int verticlesCount, uint* indices, int indicesCount, VerticleMember vmembers /*= VerticleMember::POS_COLOR_TEXCOORD&*/)
{
	setupGLData(vertices, verticlesCount, indices, indicesCount, vmembers);
}

void Mesh::draw()
{
	if (!this->m_setuped || this->m_verticesCount <= 0) return;


	glBindVertexArray(m_vao);
	if (m_indicesCount > 0)
	{
		glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, m_verticesCount);
	}
	
	glBindVertexArray(0);
}

END_NAMESPACE