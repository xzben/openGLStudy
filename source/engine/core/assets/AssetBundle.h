#pragma once
#include "common.h"
#include "core/base/Object.h"
#include "items/Asset.h"
#include <unordered_map>
#include <string>
BEGIN_OGS_NAMESPACE

class Asset;


class AssetBundle : public Asset
{
	DECLARE_CLASS(AssetBundle)
public:
	AssetBundle();
	AssetBundle(const std::string& path);

	const AutoRef<Asset> getAsset(const std::string& name);
	void releaseAsset(const std::string& name);

	virtual void onLoad(const AutoRef<Data>& data) override;
	virtual void onUnload() override;
private:
	std::unordered_map<std::string, AutoRef<Asset>> m_assets;
};
END_OGS_NAMESPACE