#pragma once

#include "Asset.h"

BEGIN_OGS_NAMESPACE

class Scene;

class AssetScene : public Asset
{
	DECLARE_CLASS(AssetScene)
	DECLARE_REFLEX_CLASS_FIELD(AssetScene);
public:
	virtual void onLoad(const AutoRef<Data>& data)override;
	virtual void onUnload()override;
	Scene* getScene() { return m_scene; }
	void setScene(Scene* scene) { m_scene = scene; }
protected:
	Scene* m_scene{ nullptr };
};

END_OGS_NAMESPACE