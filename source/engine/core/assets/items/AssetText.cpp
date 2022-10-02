#include "AssetText.h"
#include "core/filesystem/Data.h"

BEGIN_OGS_NAMESPACE

IMPLEMENT_CLASS(AssetText)

void AssetText::onLoad(const AutoRef<Data>& data)
{
	m_content = (char*)data->getData();
}

void AssetText::onUnload()
{

}


END_OGS_NAMESPACE