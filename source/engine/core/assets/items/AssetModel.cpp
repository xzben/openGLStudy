#include "AssetModel.h"
#include "core/filesystem/Data.h"
#include "core/assets/items/AssetMesh.h"
#include "core/assets/AssetsMgr.h"
BEGIN_OGS_NAMESPACE

IMPLEMENT_CLASS(AssetModel)

void AssetModel::loadAsset()
{
	if (m_loaded) return;
	if (!checkAssetValid()) return;

	m_loaded = true;
}


AssetMaterial* AssetModel::getMaterial(int index)
{
	if (index > m_materials.size()) return nullptr;

	return m_materials[index].get();
}

void AssetModel::onLoad(const AutoRef<Data>& data)
{

}

void AssetModel::onUnload()
{

}

END_OGS_NAMESPACE