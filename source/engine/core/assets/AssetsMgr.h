#pragma once

#include "common.h"
#include "core/tool/Singleton.h"
#include "asset_types.h"
#include "AssetItems.h"
#include <unordered_map>

BEGIN_OGS_GFX_NAMESPACE
class Texture;
END_OGS_GFX_NAMESPACE

BEGIN_OGS_NAMESPACE

class AssetsMgr : public Singleton<AssetsMgr>
{
public:
	static AssetType GetAssetType(const std::string& filename);
	static Asset* CreateAsset(const std::string& path);

	Asset* getAsset(const std::string& path, bool create = true);

	template<typename T>
	T* getAsset(const std::string& path, bool create = true)
	{
		Asset* asset = getAsset(path, create);

		return asset->ToCast<T>();
	}

	void   releaseAsset(Asset* asset);

	OGS::Gfx::Texture* getTexure(const std::string& path);
protected:
	std::unordered_map<std::string, AutoRef<Asset>> m_assets;
	std::unordered_map<std::string, AutoRef<OGS::Gfx::Texture>> m_loadedTextures;
};
END_OGS_NAMESPACE