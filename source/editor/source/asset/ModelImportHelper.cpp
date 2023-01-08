#include "ModelImportHelper.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "core/assets/AssetItems.h"
using namespace OGS;

BEGIN_EDITOR_NAMESPACE

static SubMesh* processSubMesh(AssetModel* mode, aiMesh* mesh, const aiScene* scene)
{
	SubMesh* subMesh = SubMesh::create();

	// fill attributes
	//subMesh->m_attributes.push_back(Attribute(AttributeName::ATTR_POSITION));
	//if (mesh->HasNormals())
	//{
	//	subMesh->m_attributes.push_back(Attribute(AttributeName::ATTR_NORMAL));
	//}

	//if (mesh->mTextureCoords[0])
	//{
	//	subMesh->m_attributes.push_back(Attribute(AttributeName::ATTR_TEX_COORD));
	//	subMesh->m_attributes.push_back(Attribute(AttributeName::ATTR_TANGENT));
	//	subMesh->m_attributes.push_back(Attribute(AttributeName::ATTR_BITANGENT));
	//}

	//// file vertex datas
	//for (uint32 i = 0; i < mesh->mNumVertices; i++)
	//{
	//	subMesh->m_vertexBuffer.writeFloat(mesh->mVertices[i].x);
	//	subMesh->m_vertexBuffer.writeFloat(mesh->mVertices[i].y);
	//	subMesh->m_vertexBuffer.writeFloat(mesh->mVertices[i].z);

	//	if (mesh->HasNormals())
	//	{
	//		subMesh->m_vertexBuffer.writeFloat(mesh->mNormals[i].x);
	//		subMesh->m_vertexBuffer.writeFloat(mesh->mNormals[i].y);
	//		subMesh->m_vertexBuffer.writeFloat(mesh->mNormals[i].z);
	//	}

	//	if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
	//	{
	//		subMesh->m_vertexBuffer.writeFloat(mesh->mTextureCoords[0][i].x);
	//		subMesh->m_vertexBuffer.writeFloat(mesh->mTextureCoords[0][i].y);

	//		subMesh->m_vertexBuffer.writeFloat(mesh->mTangents[i].x);
	//		subMesh->m_vertexBuffer.writeFloat(mesh->mTangents[i].y);
	//		subMesh->m_vertexBuffer.writeFloat(mesh->mTangents[i].z);

	//		subMesh->m_vertexBuffer.writeFloat(mesh->mBitangents[i].x);
	//		subMesh->m_vertexBuffer.writeFloat(mesh->mBitangents[i].y);
	//		subMesh->m_vertexBuffer.writeFloat(mesh->mBitangents[i].z);
	//	}
	//}

	////fill index datas
	//int indexSize = 0;
	//// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	//for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	//{
	//	indexSize += mesh->mFaces[i].mNumIndices;
	//}
	//subMesh->m_indexBuffer.reverse(indexSize * sizeof(uint32));
	//// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	//for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	//{
	//	const aiFace& face = mesh->mFaces[i];
	//	// retrieve all indices of the face and store them in the indices vector
	//	for (unsigned int j = 0; j < face.mNumIndices; j++)
	//		subMesh->m_indexBuffer.writeUInt32(face.mIndices[j]);
	//}

	return subMesh;
}

AssetMesh* processMesh(AssetModel* model, aiNode* node, const aiScene* scene)
{
	AssetMesh* assetMesh = AssetMesh::create();
	for (uint32 i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		/*	SubMesh* submesh = processSubMesh(model, mesh, scene);
			assetMesh->m_subMeshs.push_back(submesh);
			assetMesh->m_subMeshMaterials.push_back(model->getMaterial(mesh->mMaterialIndex));*/
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processMesh(model, node->mChildren[i], scene);
	}

	return assetMesh;
}
enum class TextureSampleType
{
	DIFFUSE,
	SPECULAR,
	AMBIENT,
	HEIGHT,
	NORMAL,
};
static struct LoadTextureConfig {
	aiTextureType type;
	const char* name;
	TextureSampleType sampleType;
}s_LoadTextureTypes[] = {
	{ aiTextureType_DIFFUSE, "diffuse", TextureSampleType::DIFFUSE }, // 纹理和 漫反射结果相结合
	{ aiTextureType_SPECULAR, "specular" , TextureSampleType::SPECULAR}, //纹理和 镜面反射相结合
	{ aiTextureType_AMBIENT, "ambient", TextureSampleType::AMBIENT}, // 环境光
	//{ aiTextureType_EMISSIVE, "emissive"},
	{ aiTextureType_HEIGHT, "height", TextureSampleType::HEIGHT}, //高度贴图
	{ aiTextureType_NORMALS, "normals", TextureSampleType::NORMAL}, //法线贴图
	//{ aiTextureType_SHININESS, "shininess"}, //亮度贴图
	//{ aiTextureType_OPACITY, "opacity"},  // 透明度贴图
	//{ aiTextureType_DISPLACEMENT, "displacement"}, // 位移贴图
	//{ aiTextureType_LIGHTMAP, "lightmap"}, // lightmap 
	//{ aiTextureType_REFLECTION, "reflection"}, //
};

const int loadTextureSize = sizeof(s_LoadTextureTypes);

AssetMaterial* processMaterials(const std::string& path, aiMaterial* mat, const aiScene* scene)
{
	AssetMaterial* assetMat = AssetMaterial::create();

	for (int i = 0; i < loadTextureSize; i++)
	{
		const LoadTextureConfig& config = s_LoadTextureTypes[i];
		int count = mat->GetTextureCount(config.type);
		for (unsigned int j = 0; j < count; j++)
		{
			aiString str;
			mat->GetTexture(config.type, j, &str);

			std::string texturepath = path + "/" + str.C_Str();
			/*Texture* tex = OGS::AssetsMgr::getInstance()->getTexure(texturepath);
			tex->setSampeType(config.sampleType);
			tex->setIndex(j);
			tex->setSampleTypeName(config.name);
			assetMat->m_textures.push_back(tex);*/
		}
	}

	return assetMat;
}

OGS::AssetModel* ModelImportHelper::GetModelFromFile(const std::string& filepath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		CCLOG("ERROR::ASSIMP:: ", importer.GetErrorString());
		return nullptr;
	}
	std::string directory = FileSystem::getInstance()->getPath(filepath);

	for (int i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* m = scene->mMaterials[i];
		AssetMaterial* mat = processMaterials(directory, m, scene);
		mat->setName(m->GetName().C_Str());
		//m_materials.push_back(mat);
	}

	// process ASSIMP's root node recursively
	//m_mesh = processMesh(this, scene->mRootNode, scene);

	return nullptr;
}

END_EDITOR_NAMESPACE