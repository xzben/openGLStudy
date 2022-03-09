#include "Mesh.h"
#include <glad/glad.h>
#include "base/shader.h"
#include "render/Texture.h"


Mesh::Mesh()
	: vertices(nullptr)
	, indices(nullptr)
	, m_setuped(false)
	, m_vbo(0)
	, m_vao(0)
	, m_ebo(0)
	, verticesCount(0)
	, indicesCount(0)
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
}

Mesh::~Mesh()
{
	DELETE_OBJ(vertices);
	DELETE_OBJ(indices);
}


void Mesh::setup()
{

	if (this->m_setuped) return;
	this->m_setuped = true;

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, verticesCount, vertices, GL_STATIC_DRAW);
	//指定pos 属性
	glVertexAttribPointer(SHADER_POS_INDEX, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(SHADER_POS_INDEX);

	//指定color 属性
	glVertexAttribPointer(SHADER_COLOR_INDEX, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(SHADER_COLOR_INDEX);

	//指定纹理坐标 属性
	glVertexAttribPointer(SHADER_TEXCOORD__INDEX, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(SHADER_TEXCOORD__INDEX);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount, indices, GL_STATIC_DRAW);

	


	//取消buffer激活状态
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::draw(Shader* shader /*= nullptr*/, Texture* tex /*= nullptr*/, SubTexture* texs /*= nullptr*/, int subTextCount /*= 0*/)
{
	if (tex) tex->use(SHADER_MAIN_TEXTURE_INDEX);

	
	if (shader) {
		shader->use();
		shader->setInt(SHADER_MAIN_TEXTURE_NAME, SHADER_MAIN_TEXTURE_INDEX);

		//添加子纹理
		for (int i = 0; i < subTextCount; i++)
		{
			SubTexture* subtex = texs + i;
			subtex->tex->use(i + 1);
			shader->setInt(subtex->name.c_str(), i + 1);
		}
	}

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	if (shader) shader->unuse();
}
