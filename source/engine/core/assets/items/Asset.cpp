#include "Asset.h"
#include <unordered_map>
#include "core/filesystem/FileSystem.h"
#include "core/filesystem/Data.h"


BEGIN_OGS_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(Asset)
IMPLEMENT_REFLEX_CLASS_BASE(Asset)

BEGIN_REFLEX_CLASS_FIELD(Asset)
REFLEX_FIELD(int, m_type)
END_REFLEX_CLASS_FIELD()



END_OGS_NAMESPACE

BEGIN_OGS_NAMESPACE

Asset::Asset()
{

}

Asset::Asset(const std::string& path)
{
	setPath(path);
}

Asset::~Asset()
{

}

void Asset::loadAsset()
{
	if (m_loaded) return;

	AutoRef<Data> data = new Data();
	FileSystem::GetInstance()->getContentData(m_path, data);
	this->onLoad(data);
}

void Asset::unloadAsset()
{
	if (!m_loaded)return;
	this->onUnload();
	m_loaded = false;
}

END_OGS_NAMESPACE