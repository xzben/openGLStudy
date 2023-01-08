#pragma once

#include "Asset.h"
#include <unordered_map>

BEGIN_OGS_NAMESPACE
class Texture;

class AssetMaterial : public Asset
{
	friend class AssetModel;
	DECLARE_CLASS(AssetMaterial)
public:
	virtual void onLoad(const AutoRef<Data>& data)override;
	virtual void onUnload()override;
	HASH_CODE  hash() { return (HASH_CODE)this; }
	const std::string& getName() { return m_name; }
	void setName(const std::string& name) { m_name = name; }
	void setName(const char* name) { m_name = name; }
protected:
	bool m_batch;  // 合并定点合批drawcall
	bool m_instancing; // 利用gpu instance 合批
	//std::unordered_map<std::string, ShaderMacro> m_macros;
	//std::unordered_map<std::string, MaterialProperty> m_propertys;
	std::vector<AutoRef<Texture>> m_textures;
	std::string m_name;
};

END_OGS_NAMESPACE