#ifndef __2022_03_22_RESOURCE_MANAGER_H__
#define __2022_03_22_RESOURCE_MANAGER_H__

#include"common.h"
#include <unordered_map>

BEGIN_NAMESPACE

class Shader;
class Texture;
class Mesh;

enum class BuiltInShader {
	IMAGE_SHADER,  //图片使用的shader
	STANDARD_SHADER, //标准shader
	SKY_BOX, // 天空盒shader

	BUILTIN_SIZE,
};

enum class BuiltinMesh
{
	
};

class ResourceManager
{
protected:
	std::unordered_map<BuiltInShader, Shader*> m_builtinShaders;
	std::unordered_map<std::string, Shader*>   m_loadedShaders;
	std::unordered_map<std::string, Texture*>  m_loadedTextures;
	std::unordered_map<std::string, Mesh*>     m_loadedMeshs;
public:
	static ResourceManager* getInstance();

	Shader* getBuiltinShader(BuiltInShader id, bool autoRetain = true);

	Texture* loadTexture(const std::string& filename, bool autoRetain = true);
	Mesh* loadMesh(const std::string& filename, bool autoRetain = true);
	Shader* loadShader(const std::string& filename, bool autoRetain = true);
};

END_NAMESPACE

#endif//__2022_03_22_RESOURCE_MANAGER_H__