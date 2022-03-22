#include "BoxRender.h"
#include "render/Texture.h"
#include "render/base/Mesh.h"
#include "base/Shader.h"
#include "resource/ResourceManager.h"

BoxRender::BoxRender()
	: m_texture(nullptr)
	, m_mesh(nullptr)
{
	this->m_mesh = new Mesh();
	this->m_shader = ResourceManager::getInstance()->getBuiltinShader(OGS::BuiltInShader::IMAGE_SHADER);
}

BoxRender::~BoxRender()
{
	SAFE_DEL_REF(this->m_shader);
	SAFE_DEL_REF(this->m_texture);
	SAFE_DEL_REF(this->m_mesh);
}

const int IMAGE_VERTICLE_SIZE = 8 * 8;

bool BoxRender::init()
{
	this->m_texture = ResourceManager::getInstance()->loadTexture("container.jpg");
	if (this->m_texture == nullptr)
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

void BoxRender::render()
{
	this->doDraw(this->m_mesh, this->m_shader, this->m_texture);
}