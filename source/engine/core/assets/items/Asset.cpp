#include "Asset.h"
#include <unordered_map>
#include "core/filesystem/FileSystem.h"
#include "core/filesystem/Data.h"
BEGIN_OGS_NAMESPACE

IMPLEMENT_CLASS(Asset)

static std::unordered_map<std::string, AssetType> Suffix2AssetType{
	{ "png", AssetType::TImage },
	{ "jpeg", AssetType::TImage },
	{ "jpg", AssetType::TImage },

	{ "obj", AssetType::TModel },
	{ "json", AssetType::TJson },
	{ "lua", AssetType::TLua },
	{ "luac", AssetType::TLua },

	{ "mat", AssetType::TMaterial },
	{ "fs", AssetType::TShader },
	{ "vs", AssetType::TShader },

	{ "txt", AssetType::TTxt },

	{ "prefab", AssetType::TPrefab },
	{ "scene", AssetType::TScene },
};

AssetType Asset::GetAssetType(const std::string& filename)
{
	std::string ext = FileSystem::GetInstance()->getFileExt(filename);
	auto it = Suffix2AssetType.find(ext);
	if (it == Suffix2AssetType.end())
	{
		return AssetType::TUnknow;
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