#include "Material.h"
#include "base/Shader.h"
#include "resource/ResourceManager.h"

BEGIN_NAMESPACE

Material::Material(int shaderId)
	: m_texture(nullptr)
{
	m_shader = ResourceManager::getInstance()->getBuiltinShader((BuiltInShader)shaderId);
}

Material::Material(Shader* shader)
	:m_texture(nullptr)
{
	m_shader = shader;
}

Material::~Material()
{
	m_shader->delRef();
}

END_NAMESPACE