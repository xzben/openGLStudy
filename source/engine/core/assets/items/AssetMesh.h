#pragma once

#include "Asset.h"
#include "core/filesystem/Data.h"



BEGIN_OGS_NAMESPACE

class AssetMaterial;

class SubMesh : public Object
{
	friend class AssetMesh;
	friend class AssetModel;
	DECLARE_RUNTIME_CLASS(SubMesh)
public:
	SubMesh();
	virtual ~SubMesh();
protected:
	//PrimitiveMode m_primitiveMode{PrimitiveMode::TRIANGLE_LIST}; //绘制图形类型
	uint8 m_meshIndex{0}; // 在mesh中的index
	AssetMesh* m_mesh{ nullptr }; //所属mesh
	///std::vector<Attribute> m_attributes;
	//Data       m_vertexBuffer;
	//Data       m_indexBuffer;
};

class AssetMesh : public Asset
{
	DECLARE_CLASS(AssetMesh)
	friend class AssetModel;
public:
	virtual void onLoad(const AutoRef<Data>& data)override;
	virtual void onUnload()override;
	
	HASH_CODE  hash() { return (HASH_CODE)this; }
	uint8 getSubMeshCount() { return m_subMeshs.size(); }
protected:
	std::vector<AutoRef<SubMesh>> m_subMeshs;
	std::vector<AutoRef<AssetMaterial>> m_subMeshMaterials;
};

END_OGS_NAMESPACE