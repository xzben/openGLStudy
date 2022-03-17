#include "ImageComponent.h"
#include "render/Texture.h"
#include <glad/glad.h>
#include "base/Shader.h"
#include "render/base/Mesh.h"

const int IMAGE_VERTICLE_SIZE = 4 * 8;

ImageComponent::ImageComponent(const std::string& filename)
	:ImageComponent()
{
	this->init(filename);
}

ImageComponent::ImageComponent()
	: m_texture(nullptr)
	, m_mesh(nullptr)
	, m_vao(0)
{
	this->m_texture = new Texture();
	this->m_mesh = new Mesh();
	this->m_shader = new Shader("image_shader.vs", "image_shader.fs");
}

ImageComponent::~ImageComponent() 
{
	DELETE_OBJ(this->m_mesh);
	DELETE_OBJ(this->m_texture);
	DELETE_OBJ(this->m_shader);
}

bool ImageComponent::init(const std::string& filename)
{
	if(!this->m_texture->init(filename))
		return false;

	float vertices[IMAGE_VERTICLE_SIZE] = {
		-0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // ×óÏÂ½Ç
		0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // ÓÒÏÂ½Ç
		0.25f, 0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // ÓÒÉÏ½Ç
		-0.25f, 0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // ×óÉÏ½Ç
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	this->m_mesh->setup(vertices, 4, indices, 6);

	return true;
}

void ImageComponent::render()
{
	this->doDraw(this->m_mesh, this->m_shader, this->m_texture);
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