#pragma once

#include "Asset.h"

BEGIN_OGS_NAMESPACE

class SubMesh;
class AssetMesh;
class AssetMaterial;

class AssetModel : public Asset
{
	DECLARE_CLASS(AssetModel)
public:
	virtual void loadAsset();

	virtual void onLoad(const AutoRef<Data>& data)override;
	virtual void onUnload()override;
	AssetMaterial* getMaterial(int index);
protected:
	std::vector<AutoRef<AssetMaterial>> m_materials;
	AutoRef<AssetMesh> m_mesh;
};

END_OGS_NAMESPACE