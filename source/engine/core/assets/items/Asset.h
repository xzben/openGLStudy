#pragma once

#include "common.h"
#include "core/base/Object.h"
#include "core/reflex/reflex.h"

BEGIN_OGS_NAMESPACE

class Data;

class Asset : public Object
{
	DECLARE_RUNTIME_CLASS(Asset)
	DECLARE_REFLEX_CLASS(Asset);
	DECLARE_REFLEX_CLASS_FIELD(Asset);
public:
	Asset();
	Asset(const std::string& path);
	virtual ~Asset();

	void setPath(const std::string& path) { m_path = path; }
	const std::string& getPath() { return m_path; }
	const std::string& getGUID() const;
	void loadAsset();
	void unloadAsset();
	virtual void onLoad(const AutoRef<Data>& data) {};
	virtual void onUnload(){};
protected:
	void setGUID(const std::string& guid);
public:

protected:
	bool m_loaded{ false };
	AssetType m_type{AssetType::Unknow};
	std::string m_guid{ "" };
	std::string m_path{ "" };
};
END_OGS_NAMESPACE