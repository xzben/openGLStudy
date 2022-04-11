#include "ResourceManager.h"
#include "base/Shader.h"
#include "render/Texture.h"
#include "render/base/Mesh.h"
#include "base/Shader.h"

BEGIN_NAMESPACE

struct ShaderFiles 
{
	const char* vs_file;
	const char* fs_file;
};

static struct ShaderFiles s_ShaderResource[] = {
	{ "shader/image_shader.vs", "shader/image_shader.fs" },
	{ "shader/common/standard.vs", "shader/common/standard.fs" },
	{ "shader/skybox/skybox.vs", "shader/skybox/skybox.fs", },
};

ResourceManager* ResourceManager::getInstance()
{
	static ResourceManager s_instance;

	return &s_instance;
}

static Shader* createBuiltinShader(BuiltInShader id) 
{
	ShaderFiles files = s_ShaderResource[(int)id];

	return new Shader(files.vs_file, files.fs_file);
}

Shader* ResourceManager::getBuiltinShader(BuiltInShader id, bool autoRetain /*= true*/)
{
	auto it = m_builtinShaders.find(id);

	Shader* shader = nullptr;
	if (it != m_builtinShaders.end())
	{
		shader = it->second;
	}
	else 
	{
		shader = createBuiltinShader(id);
		m_builtinShaders.insert(std::pair<BuiltInShader, Shader*>(id, shader));
	}

	shader = shader->clone();

	if (autoRetain && shader)
	{
		shader->addRef();
	}

	return shader;
}


Texture* ResourceManager::loadTexture(const std::string& filename, bool autoRetain /*= true*/)
{
	auto it = m_loadedTextures.find(filename);
	Texture* tex = nullptr;

	if (it != m_loadedTextures.end()) 
	{
		tex = it->second;
	}
	else
	{
		tex = new Texture();
		tex->init(filename);

		m_loadedTextures.insert(std::pair<std::string, Texture*>(filename, tex));
	}

	if (autoRetain && tex != nullptr)
	{
		tex->addRef();
	}

	return tex;
}

Mesh* ResourceManager::loadMesh(const std::string& filename, bool autoRetain /*= true*/)
{
	return new Mesh();
}

Shader* ResourceManager::loadShader(const std::string& filename, bool autoRetain /*= true*/)
{
	auto it = m_loadedShaders.find(filename);
	Shader* shader = nullptr;

	if (it != m_loadedShaders.end())
	{
		shader = it->second;
	}
	else
	{
		shader = new Shader(filename);
		m_loadedShaders.insert(std::pair<std::string, Shader*>(filename, shader));
	}

	shader = shader->clone();

	if (autoRetain && shader != nullptr)
	{
		shader->addRef();
	}

	return shader;
}

END_NAMESPACE