#include "Material.h"
#include "base/Shader.h"
#include "render/Texture.h"
#include "render/RenderData.h"
#include "render/RenderableComponent.h"

BEGIN_NAMESPACE

Material::Material(BuiltInShader shaderId)
{
	Shader* shader = ResourceManager::getInstance()->getBuiltinShader(shaderId, false);
	this->init(shader, nullptr);
}

Material::Material(Shader* shader)
{
	this->init(shader, nullptr);
}

Material::Material(Shader* shader, Texture* mainTexture)
{
	this->init(shader, mainTexture);
}

Material::Material(BuiltInShader shaderId, Texture* mainTexture)
{
	Shader* shader = ResourceManager::getInstance()->getBuiltinShader(shaderId, false);
	this->init(shader, mainTexture);
}

Material::Material(Shader* shader, const std::string& texturepath)
{
	Texture* mainTexture = ResourceManager::getInstance()->loadTexture(texturepath, false);
	this->init(shader, mainTexture);
}

Material::Material(BuiltInShader shaderId, const std::string& texturepath)
{
	Texture* mainTexture = ResourceManager::getInstance()->loadTexture(texturepath, false);
	Shader* shader = ResourceManager::getInstance()->getBuiltinShader(shaderId, false);

	this->init(shader, mainTexture);
}


void Material::init(Shader* shader, Texture* mainTexture)
{
	this->m_mainTexture = mainTexture;
	if(m_mainTexture)
		this->m_mainTexture->addRef();

	this->m_shader = shader;
	if(this->m_shader)
		this->m_shader->addRef();
}

void Material::setSubTexture(const std::string& name, Texture* tex)
{
	SubTexture* subTex = nullptr;
	auto itor = this->m_mapSubTextures.find(name);
	if (itor == m_mapSubTextures.end())
	{
		if (tex != nullptr)
		{
			subTex = new SubTexture();
			subTex->name = name;
			subTex->tex = tex;
			tex->addRef();

			this->m_subTextures.push_back(subTex);
			this->m_mapSubTextures.insert(std::pair<std::string, SubTexture*>(name, subTex));
		}
	}
	else
	{
		subTex = itor->second;
		
		if (tex == nullptr)
		{
			this->m_mapSubTextures.erase(itor);
			for (auto it = m_subTextures.begin(); it != m_subTextures.end(); it++)
			{
				if ((*it)->name == name)
				{
					m_subTextures.erase(it);
					break;
				}
			}
		}
		else
		{
			if (subTex->tex != tex) {
				SAFE_DEL_REF(subTex->tex);
				subTex->tex = tex;
				tex->addRef();
			}
		}
	}
}

Material::~Material()
{
	SAFE_DEL_REF(m_shader);
	SAFE_DEL_REF(m_mainTexture);

	for (auto it = m_subTextures.begin(); it != m_subTextures.end(); it++)
	{
		SubTexture* sub = *it;
		delete sub;
	}

	for (auto it = m_uniforms.begin(); it != m_uniforms.end(); it++)
	{
		Unifrom* uniform = *it;
		delete uniform;
	}
}

bool Material::beforeDraw(RenderData* render, RenderableComponent* com)
{
	if (m_shader)
	{
		m_shader->use();
		m_shader->initCommonUniform(render, com->getNode());

		if (m_mainTexture)
		{
			m_mainTexture->use(SHADER_MAIN_TEXTURE_INDEX);
			m_shader->setInt(SHADER_MAIN_TEXTURE_NAME, SHADER_MAIN_TEXTURE_INDEX);
		}

		int subIndex = 1;
		for (auto it = m_subTextures.begin(); it != m_subTextures.end(); it++)
		{
			SubTexture* sub = *it;

			if (sub->tex) {
				sub->tex->use(subIndex);
				m_shader->setInt(sub->name.c_str(), subIndex);
			}
			subIndex++;
		}

		for (auto it = m_uniforms.begin(); it != m_uniforms.end(); it++)
		{
			Unifrom* uniform = *it;
			m_shader->setFloatValues(uniform->name, uniform->values, uniform->size);
		}
	}

	return true;
}

bool Material::afterDraw()
{
	if (m_shader)
	{
		m_shader->unuse();
	}
	if (m_mainTexture) m_mainTexture->unuse();

	for (auto it = m_subTextures.begin(); it != m_subTextures.end(); it++)
	{
		SubTexture* sub = *it;
		if (sub->tex) {
			sub->tex->unuse();
		}
	}

	return true;
}

Unifrom* Material::getUniform(const std::string& name)
{
	auto it = this->m_mapUnifroms.find(name);
	if (it == m_mapUnifroms.end()) {
		return nullptr;
	}

	return it->second;
}

void Material::pushUniform(const std::string& name, Unifrom* uniform)
{
	this->m_mapUnifroms.insert(std::pair<std::string, Unifrom*>(name, uniform));
	this->m_uniforms.push_back(uniform);
}

void Material::setUniform(const std::string& name, const fVec3& value)
{
	Unifrom* uniform = getUniform(name);

	if (uniform == nullptr)
	{
		uniform = new Unifrom();
		uniform->name = name;
		uniform->size = 3;
		uniform->v3 = value;
		
		this->pushUniform(name, uniform);
	}
	else
	{
		uniform->size = 3;
		uniform->v3 = value;
	}
}

void Material::setUniform(const std::string& name, const Color& value)
{
	Unifrom* uniform = getUniform(name);

	if (uniform == nullptr)
	{
		uniform = new Unifrom();
		uniform->name = name;
		uniform->size = 4;
		uniform->color = value;

		this->pushUniform(name, uniform);
	}
	else
	{
		uniform->size = 4;
		uniform->color = value;
	}
}

void Material::setUniform(const std::string& name, const RGB& value)
{
	Unifrom* uniform = getUniform(name);

	if (uniform == nullptr)
	{
		uniform = new Unifrom();
		uniform->name = name;
		uniform->size = 3;
		uniform->rgb = value;

		this->pushUniform(name, uniform);
	}
	else
	{
		uniform->size = 3;
		uniform->rgb = value;
	}
}

void Material::setUniform(const std::string& name, const fVec4& value)
{
	Unifrom* uniform = getUniform(name);

	if (uniform == nullptr)
	{
		uniform = new Unifrom();
		uniform->name = name;
		uniform->size = 4;
		uniform->v4 = value;

		this->pushUniform(name, uniform);
	}
	else
	{
		uniform->size = 4;
		uniform->v4 = value;
	}
}

void Material::setUniform(const std::string& name, const float value)
{
	Unifrom* uniform = getUniform(name);

	if (uniform == nullptr)
	{
		uniform = new Unifrom();
		uniform->name = name;
		uniform->size = 1;
		uniform->v1 = value;

		this->pushUniform(name, uniform);
	}
	else
	{
		uniform->size = 1;
		uniform->v1 = value;
	}
}

void Material::setUniform(const std::string& name, const fVec2& value)
{
	Unifrom* uniform = getUniform(name);

	if (uniform == nullptr)
	{
		uniform = new Unifrom();
		uniform->name = name;
		uniform->size = 2;
		uniform->v2 = value;

		this->pushUniform(name, uniform);
	}
	else
	{
		uniform->size = 2;
		uniform->v2 = value;
	}
}

END_NAMESPACE