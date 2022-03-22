#include "BoxRender.h"
#include "render/Texture.h"
#include "render/base/Mesh.h"
#include "base/Shader.h"

BoxRender::BoxRender()
	: m_texture(nullptr)
	, m_mesh(nullptr)
	, m_shader(nullptr)
{
	this->m_texture = new Texture();
	this->m_mesh = new Mesh();
	this->m_shader = new Shader("image_shader.vs", "image_shader.fs");
}

BoxRender::~BoxRender()
{

}

const int IMAGE_VERTICLE_SIZE = 4 * 8;

bool BoxRender::init()
{
	if (!this->m_texture->init("container.jpg"))
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