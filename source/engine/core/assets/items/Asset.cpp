#include "Asset.h"
#include <unordered_map>
#include "core/filesystem/FileSystem.h"
#include "core/filesystem/Data.h"
#include "utils/Utils.h"

BEGIN_OGS_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(Asset)
IMPLEMENT_REFLEX_CLASS_BASE(Asset)

BEGIN_REFLEX_CLASS_FIELD(Asset)
REFLEX_FIELD_NAME(int, m_type, "type")
REFLEX_FIELD_GETSET(std::string, "guid", &Asset::getGUID, &Asset::setGUID)
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

void Asset::setGUID(const std::string& guid)
{
	m_guid = guid;
}

const std::string& Asset::getGUID() const
{
	if (m_guid == "")
	{
		((Asset*)this)->m_guid = Utils::create_guide();
	}

	return m_guid;
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