#include "Material.h"
#include "base/Shader.h"
#include "render/Texture.h"
#include "render/RenderData.h"
#include "render/RenderableComponent.h"
#include "utils/Utils.h"


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
	m_depthTest = true;
	m_depthWriteable = true;
	m_depthFunc = DepthFunc::LESS;

	m_stencilTest = false;
	m_stencilWriteMask = 0xff;
	m_stencilMask = 0xff;
	m_stecilRef = 1;
	m_stencilFunc = StencilFunc::EQUAL;
	m_sfail = StencilOp::KEEP;
	m_dpfail = StencilOp::KEEP;
	m_dppass = StencilOp::KEEP;

	m_blend = false;
	m_blendSrc = BlendFunc::SRC_ALPHA;
	m_blendDst = BlendFunc::ONE_MINUS_DST_ALPHA;

	m_enableCullFace = false;
	m_frontface = FrontFace::CW;
	m_cullface = CullFace::BACK;

	m_defineChange = false;
	this->m_mainTexture = mainTexture;
	if(m_mainTexture)
		this->m_mainTexture->addRef();

	this->m_shader = shader;
	if(this->m_shader)
		this->m_shader->addRef();
}

void Material::setMainTexture(Texture* mainTexture)
{
	this->m_mainTexture = mainTexture;
	if (m_mainTexture)
		this->m_mainTexture->addRef();

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

	for (auto it = m_defines.begin(); it != m_defines.end(); it++)
	{
		delete* it;
	}
}

void Material::setEnableDepthTest(bool enable)
{
	m_depthTest = enable;
}
void Material::setEnableDepthWrite(bool enable)
{
	m_depthWriteable = enable;
}

void Material::setDepthFunc(DepthFunc func)
{
	m_depthFunc = func;
}

bool Material::beforeDraw(RenderData* render, RenderableComponent* com)
{
	//是否启用深度测试
	if (m_depthTest)
	{
		glEnable(GL_DEPTH_TEST);
		//是否启用深度写入

		m_depthWriteable ? glDepthMask(GL_TRUE) : glDepthMask(GL_FALSE);
		glDepthFunc((uint)m_depthFunc);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
	
	//模板测试
	if (m_stencilTest)
	{
		glEnable(GL_STENCIL_TEST);
		glStencilMask(m_stencilWriteMask);
		glStencilFunc((uint)m_stencilFunc, m_stecilRef, m_stencilMask);
		glStencilOp((uint)m_sfail, (uint)m_dpfail, (uint)m_dppass);
	}
	else
	{
		glDisable(GL_STENCIL_TEST);
	}

	if (m_blend)
	{
		glEnable(GL_BLEND);
		glBlendFunc((uint)m_blendSrc, (uint)m_blendDst);
	}
	else
	{
		glDisable(GL_BLEND);
	}

	if (m_enableCullFace)
	{
		glEnable(GL_CULL_FACE);
		glCullFace((uint)m_cullface);
		glFrontFace((uint)m_frontface);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}

	if (m_shader)
	{
		if (m_defineChange)
		{
			m_shader->recompile(&m_defines);
			m_defineChange = false;
		}

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

Unifrom* Material::getUniform(const std::string& name, bool create /*= false*/)
{
	auto it = this->m_mapUnifroms.find(name);
	if (it == m_mapUnifroms.end()) 
	{
		if (create)
		{
			auto uniform = new Unifrom();
			uniform->name = name;
			this->pushUniform(uniform);

			return uniform;
		}

		return nullptr;
	}

	return it->second;
}

void Material::pushUniform(Unifrom* uniform)
{
	this->m_mapUnifroms.insert(std::pair<std::string, Unifrom*>(uniform->name, uniform));
	this->m_uniforms.push_back(uniform);
}

void Material::setUniform(const std::string& name, const fVec3& value)
{
	Unifrom* uniform = getUniform(name, true);
	uniform->size = 3;
	uniform->v3 = value;	
}

void Material::setUniform(const std::string& name, const Color& value)
{
	Unifrom* uniform = getUniform(name, true);
	uniform->size = 4;
	uniform->color = value;
}

void Material::setUniform(const std::string& name, const RGB& value)
{
	Unifrom* uniform = getUniform(name, true);

	uniform->size = 3;
	uniform->rgb = value;
}

void Material::setUniform(const std::string& name, const fVec4& value)
{
	Unifrom* uniform = getUniform(name, true);

	uniform->size = 4;
	uniform->v4 = value;

}

void Material::setUniform(const std::string& name, const float value)
{
	Unifrom* uniform = getUniform(name, true);

	uniform->size = 1;
	uniform->v1 = value;
}

void Material::setUniform(const std::string& name, const fVec2& value)
{
	Unifrom* uniform = getUniform(name, true);
	uniform->size = 2;
	uniform->v2 = value;
}

void Material::addDefine(SHADER_DEFINE* define)
{
	this->m_mapDefines.insert(std::pair<std::string, SHADER_DEFINE*>(define->name, define));
	this->m_defines.push_back(define);
}

SHADER_DEFINE* Material::getDefine(const std::string& name, bool create /*= false*/)
{
	auto itor = m_mapDefines.find(name);
	if (itor == m_mapDefines.end())
	{
		if (create)
		{
			SHADER_DEFINE* define = new SHADER_DEFINE();

			define->name = name;
			this->addDefine(define);
			return define;
		}
		else
		{
			return nullptr;
		}

	}

	return itor->second;
}

void Material::setDefine(const std::string& name)
{
	SHADER_DEFINE* define = getDefine(name, true);

	define->value = Utils::string_format("#define %s\r\n", name.c_str());
	m_defineChange = true;
}

void Material::setDefine(const std::string& name, const std::string& value)
{
	SHADER_DEFINE* define = getDefine(name, true);
	define->value = Utils::string_format("#define %s %s\r\n", name.c_str(), value.c_str());
	m_defineChange = true;
}

void Material::setDefine(const std::string& name, float value)
{
	SHADER_DEFINE* define = getDefine(name, true);

	define->value = Utils::string_format("#define %s %.7f\r\n", name.c_str(), value);
	m_defineChange = true;
}

void Material::setDefine(const std::string& name, int value)
{
	SHADER_DEFINE* define = getDefine(name, true);
	define->value = Utils::string_format("#define %s %d\r\n", name.c_str(), value);
	m_defineChange = true;
}

void Material::deleteDefine(const std::string& name)
{
	auto itor = m_mapDefines.find(name);
	if (itor == m_mapDefines.end())
	{
		return;
	}

	this->m_mapDefines.erase(itor);

	SHADER_DEFINE* define = itor->second;
	for (auto it = m_defines.begin(); it != m_defines.end(); it++)
	{

		if (*it == define)
		{
			m_defines.erase(it);
			break;
		}
	}
	m_defineChange = true;
}

END_NAMESPACE