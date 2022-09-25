#include "AssetScene.h"
#include "core/base/Scene.h"
BEGIN_OGS_NAMESPACE

IMPLEMENT_CLASS(AssetScene)

BEGIN_REFLEX_CLASS_FIELD(AssetScene)
REFLEX_FIELD(Scene*, m_scene)
END_REFLEX_CLASS_FIELD()

END_OGS_NAMESPACE

BEGIN_OGS_NAMESPACE
void AssetScene::onLoad(SharePtr<Data>& data)
{

}

void AssetScene::onUnload()
{

}

END_OGS_NAMESPACE