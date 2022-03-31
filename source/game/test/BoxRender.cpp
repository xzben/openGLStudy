#include "BoxRender.h"
#include "render/Texture.h"
#include "base/Shader.h"
#include "resource/ResourceManager.h"
#include "CubeMesh.h"

BoxRender::BoxRender()
	: m_texture(nullptr)
	, m_mesh(nullptr)
{
	this->m_mesh = new CubeMesh();
	this->m_shader = ResourceManager::getInstance()->loadShader("cube");
}

BoxRender::~BoxRender()
{
	SAFE_DEL_REF(this->m_shader);
	SAFE_DEL_REF(this->m_texture);
	SAFE_DEL_REF(this->m_mesh);
}

void BoxRender::onLoad()
{
	RenderableComponent::onLoad();
	this->init();
}
bool BoxRender::init()
{
	this->m_texture = ResourceManager::getInstance()->loadTexture("container.jpg");
	if (this->m_texture == nullptr)
		return false;

	return true;
}

void BoxRender::render(RenderData* render)
{
	this->doDraw(render, this->m_mesh, this->m_shader, this->m_texture);
}