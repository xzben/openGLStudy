#include "ImageComponent.h"
#include "render/Texture.h"
#include <glad/glad.h>
#include "base/Shader.h"
#include "render/base/Mesh.h"
#include "resource/ResourceManager.h"

BEGIN_NAMESPACE

const int IMAGE_VERTICLE_SIZE = 4 * 8;

ImageComponent::ImageComponent(const std::string& filename)
	:ImageComponent()
{
	this->init(filename);
}

ImageComponent::ImageComponent()
	: m_texture(nullptr)
{
	this->m_mesh = new Mesh();
	this->m_shader = ResourceManager::getInstance()->getBuiltinShader(BuiltInShader::IMAGE_SHADER);
}

ImageComponent::~ImageComponent() 
{
	SAFE_DEL_REF(this->m_mesh);
	SAFE_DEL_REF(this->m_texture);
	SAFE_DEL_REF(this->m_shader);
}

bool ImageComponent::init(const std::string& filename)
{
	this->m_texture = ResourceManager::getInstance()->loadTexture(filename);

	if(this->m_texture == nullptr)
		return false;

	float vertices[IMAGE_VERTICLE_SIZE] = {
		-0.25f, -0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // ×óÏÂ½Ç
		0.25f, -0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // ÓÒÏÂ½Ç
		0.25f, 0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // ÓÒÉÏ½Ç
		-0.25f, 0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // ×óÉÏ½Ç
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

END_NAMESPACE