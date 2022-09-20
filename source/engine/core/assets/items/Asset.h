#pragma once

#include "common.h"
#include "core/base/Object.h"

BEGIN_OGS_NAMESPACE

class Data;

class Asset : public Object
{
	DECLARE_CLASS(Asset)
public:
	Asset();
	Asset(const std::string& path);

	virtual ~Asset();
	static AssetType GetAssetType(const std::string& filename);

	void setPath(const std::string& path) { m_path = path; }
	void loadAsset();
	void unloadAsset();
	virtual void onLoad(SharePtr<Data>& data) {};
	virtual void onUnload(){};
protected:
	bool m_loaded{ false };
	AssetType m_type{AssetType::TUnknow};
	std::string m_path{ "" };
};
END_OGS_NAMESPACE