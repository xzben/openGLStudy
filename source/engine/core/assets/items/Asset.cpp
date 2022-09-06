#include "Asset.h"
#include <unordered_map>
#include "core/filesystem/FileSystem.h"
BEGIN_OGS_NAMESPACE

IMPLEMENT_CLASS(Asset)

static std::unordered_map<std::string, AssetType> Suffix2AssetType{
	{ "png", AssetType::Image },
	{ "jpeg", AssetType::Image },
	{ "jpg", AssetType::Image },

	{ "obj", AssetType::Model },
	{ "json", AssetType::Json },
	{ "lua", AssetType::Lua },
	{ "luac", AssetType::Lua },

	{ "mat", AssetType::Material },
	{ "fs", AssetType::Shader },
	{ "vs", AssetType::Shader },

	{ "txt", AssetType::Txt },

	{ "prefab", AssetType::Prefab },
	{ "scene", AssetType::Scene },
};

AssetType Asset::GetAssetType(const std::string& filename)
{
	std::string ext = FileSystem::GetInstance()->getFileExt(filename);
	auto it = Suffix2AssetType.find(ext);
	if (it == Suffix2AssetType.end())
	{
		return AssetType::Unknow;
	}

	return it->second;
}

Asset::Asset(const std::string& path)
{
	m_type = Asset::GetAssetType(path);
}

Asset::~Asset()
{

}

void Asset::loadAsset()
{
	if (m_loaded) return;

	auto data = makeShare<Data>();

	FileSystem::GetInstance()->getContentData(m_path, data);
	this->onLoad(data);
	
}

void Asset::unloadAsset()
{

}

END_OGS_NAMESPACE