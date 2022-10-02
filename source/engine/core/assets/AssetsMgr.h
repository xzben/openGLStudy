#pragma once

#include "common.h"
#include "core/tool/Singleton.h"
#include "asset_types.h"
#include "items/Asset.h"
#include <unordered_map>

BEGIN_OGS_NAMESPACE

class AssetsMgr : public Singleton<AssetsMgr>
{
public:
	static AssetType GetAssetType(const std::string& filename);
	static Asset* CreateAsset(const std::string& path);

	Asset* getAsset(const std::string& path, bool create = true);
	void   releaseAsset(Asset* asset);

protected:
	std::unordered_map<std::string, AutoRef<Asset>> m_assets;
};
END_OGS_NAMESPACE