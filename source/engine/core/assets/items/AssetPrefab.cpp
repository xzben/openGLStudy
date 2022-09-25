#include "AssetPrefab.h"
#include "core/base/Node.h"
BEGIN_OGS_NAMESPACE

IMPLEMENT_CLASS(AssetPrefab)

BEGIN_REFLEX_CLASS_FIELD(AssetPrefab)
REFLEX_FIELD(Node*, m_node)
END_REFLEX_CLASS_FIELD()



END_OGS_NAMESPACE

BEGIN_OGS_NAMESPACE
void AssetPrefab::onLoad(SharePtr<Data>& data)
{

}

void AssetPrefab::onUnload()
{

}

END_OGS_NAMESPACE