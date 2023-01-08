#include "RenderableComponent.h"
#include "base/SceneManager.h"
#include "render/RenderContainor.h"
#include "base/Scene.h"
#include "base/Shader.h"
#include "render/Texture.h"
#include "render/base/Mesh.h"
#include "render/Material.h"

BEGIN_NAMESPACE

RenderableComponent::RenderableComponent()
	: m_containor(nullptr)
{

}

RenderableComponent::~RenderableComponent()
{
	
}

void RenderableComponent::onLoad()
{

}

void RenderableComponent::start() 
{
	Component::start();
	this->m_containor = SceneManager::getInstance()->getCurScene();
	if (this->m_containor) {
		this->m_containor->addRenderComp(this);
	}
}

void RenderableComponent::onPause() 
{

}

void RenderableComponent::onResume() 
{

}

void RenderableComponent::stop() 
{
	Component::stop();
	if (m_containor) {
		m_containor->removeRenderComp(this);
	}
}

void RenderableComponent::update(float dt) 
{

}

void RenderableComponent::onDestroy() 
{

}

void RenderableComponent::doDraw(RenderData* render, Mesh* mesh, Shader* shader /* = nullptr */, Texture* tex /* = nullptr */, SubTexture* texs /* = nullptr */, int subTextCount /* = 0 */)
{
	if (shader) {
		shader->use();
		shader->initCommonUniform(render, this->m_node);
		if (tex)
		{
			tex->use(SHADER_MAIN_TEXTURE_INDEX);
			shader->setInt(SHADER_MAIN_TEXTURE_NAME, SHADER_MAIN_TEXTURE_INDEX);
		}
		
		//Ìí¼Ó×ÓÎÆÀí
		for (int i = 0; i < subTextCount; i++)
		{
			SubTexture* subtex = texs + i;
			subtex->tex->use(i + 1);
			shader->setInt(subtex->name.c_str(), i + 1);
		}
	}

	mesh->draw();

	if (shader) shader->unuse();
	if (tex) tex->unuse();
	for (int i = 0; i < subTextCount; i++)
	{
		SubTexture* subtex = texs + i;
		subtex->tex->unuse();
	}
}

void RenderableComponent::doDraw(RenderData* render, Mesh* mesh, Material* material)
{
	material->beforeDraw(render, this);
	mesh->draw();
	material->afterDraw();
}

END_NAMESPACE