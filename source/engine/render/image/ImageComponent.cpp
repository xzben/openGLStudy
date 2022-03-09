#include "ImageComponent.h"
#include "render/Texture.h"
#include <glad/glad.h>
#include "base/Shader.h"

ImageComponent::ImageComponent(const std::string& filename)
	:ImageComponent()
{
	this->init(filename);
}

ImageComponent::ImageComponent()
	: m_texture(nullptr)
{
	this->m_texture = new Texture();
	this->m_shader = new Shader("image_shader.vs", "image_shader.fs");
}

ImageComponent::~ImageComponent() 
{
	delete this->m_texture;
	delete this->m_shader;
}

bool ImageComponent::init(const std::string& filename)
{
	if(!this->m_texture->init(filename))
		return false;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	float vertices[] = {
		-0.75f, -0.75f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 左下角
		-0.25f, -0.75f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 右下角
		-0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 右上角
		-0.75f, -0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // 左上角
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
		3, //每个属性的size vec3
		GL_FLOAT, //参数的类型 float
		GL_FALSE,  // 是否需要 标准话参数 GL_TRUE 则会映射到 0 - 1
		8 * sizeof(float), // 每个元素在内存中的跨副
		(void*)0); //数据在内存中的起始偏移位置

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, //location 1
		3, //每个属性的size vec2
		GL_FLOAT, //参数的类型 float
		GL_FALSE,  // 是否需要 标准话参数 GL_TRUE 则会映射到 0 - 1
		8 * sizeof(float), // 每个元素在内存中的跨副
		(void*)(3 * sizeof(float))); //数据在内存中的起始偏移位置
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, //location 2
		2, //每个属性的size vec2
		GL_FLOAT, //参数的类型 float
		GL_FALSE,  // 是否需要 标准话参数 GL_TRUE 则会映射到 0 - 1
		8 * sizeof(float), // 每个元素在内存中的跨副
		(void*)(6*sizeof(float))); //数据在内存中的起始偏移位置

	glEnableVertexAttribArray(2);

	return true;
}

void ImageComponent::render()
{
	m_texture->use();
	m_shader->use();
	m_shader->setInt("mainTexture", 0);
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

int ImageComponent::getWidth()
{
	return this->m_texture->getWidth();
}

int ImageComponent::getHeight()
{
	return this->m_texture->getHeight();
}

int ImageComponent::getChannels()
{
	return this->m_texture->getChannels();
}