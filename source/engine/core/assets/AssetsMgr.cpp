#include "AssetsMgr.h"
#include "core/assets/AssetItems.h"
#include "gfx/base/Texture.h"

BEGIN_OGS_NAMESPACE

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

AssetType AssetsMgr::GetAssetType(const std::string& filename)
{
	std::string ext = FileSystem::getInstance()->getFileExt(filename);
	auto it = Suffix2AssetType.find(ext);
	if (it == Suffix2AssetType.end())
	{
		return AssetType::Unknow;
	}

	return it->second;
}

Asset* AssetsMgr::CreateAsset(const std::string& path)
{
	AssetType type = GetAssetType(path);
	Asset* asset = nullptr;

	switch (type)
	{
	case OGS::AssetType::Lua:
		{
			asset = new AssetLua();
		}
		break;
	case OGS::AssetType::Txt:
		{
			asset = new AssetText();
		}	
		break;
	case OGS::AssetType::Json:
		{
			asset = new AssetJson();
		}
		break;
	case OGS::AssetType::Material:
		{
			asset = new AssetMaterial();
		}
		break;
	case OGS::AssetType::Model:
		{
			asset = new AssetModel();
		}
		break;
	case OGS::AssetType::Image:
		{
			asset = new AssetImage();
		}
		break;
	case OGS::AssetType::Shader:
		{
			asset = new AssetShader();
		}
		break;
	case OGS::AssetType::Prefab:
		{
			asset = new AssetPrefab();
		}
		break;
	case OGS::AssetType::Scene:
		{
			asset = new AssetScene();
		}
		break;
	}
	
	if (asset)
	{
		asset->setPath(path);
	}
	return asset;
}

Asset* AssetsMgr::getAsset(const std::string& path, bool create /*= true*/)
{
	auto itor = m_assets.find(path);
	if (itor == m_assets.end())
	{
		if (create)
		{
			auto asset = AssetsMgr::CreateAsset(path);
			m_assets.insert(std::make_pair(path, asset));

			return asset;
		}
		else
		{
			return nullptr;
		}
	}

	return itor->second.get();
}

void  AssetsMgr::releaseAsset(Asset* asset)
{
	asset->unloadAsset();
	auto it = m_assets.find(asset->getPath());
	if (it != m_assets.end())
	{
		ASSERT(it->second == asset, "same path only on asset");
		m_assets.erase(it);
	}
}

OGS::Gfx::Texture* AssetsMgr::getTexure(const std::string& path)
{
	auto it = m_loadedTextures.find(path);
	if (it != m_loadedTextures.end())
	{
		return it->second.get();
	}

	/*Texture* tex = Texture::create();
	tex->initWithFile(path);
	m_loadedTextures.insert(std::make_pair(path, tex));

	return tex;*/

	return nullptr;
}

END_OGS_NAMESPACE