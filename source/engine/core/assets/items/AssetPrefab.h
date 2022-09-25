#pragma once

#include "Asset.h"

BEGIN_OGS_NAMESPACE

class Node;

class AssetPrefab : public Asset
{
	DECLARE_CLASS(AssetPrefab)
	DECLARE_REFLEX_CLASS_FIELD(AssetPrefab);
public:
	virtual void onLoad(SharePtr<Data>& data)override;
	virtual void onUnload()override;

	Node* getNode() { return m_node; }
	void setNode(Node* node) { m_node = node; }
public:
	Node* m_node{nullptr};
};

END_OGS_NAMESPACE