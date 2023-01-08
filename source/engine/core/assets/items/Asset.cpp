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
REFLEX_FIELD_NAME(std::string, m_path, "path")
REFLEX_FIELD_NAME(std::string, m_nativePath, "nativePath")
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

void Asset::setPath(const std::string& path)
{
	m_path = path;
	m_nativePath = FileSystem::getInstance()->getFullPath(path);
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
	unloadAsset();
}

std::string Asset::getFileExt()
{
	return FileSystem::getInstance()->getFileExt(m_path);
}

bool Asset::checkAssetValid()
{
	if (!FileSystem::getInstance()->isFileExists(m_path))
	{
		ASSERT(false, "assets load failed file[%s] not exists", m_path.c_str());
		return false;
	}

	return true;
}

void Asset::loadAsset()
{
	if (m_loaded) return;
	if (!checkAssetValid()) return;

	m_loaded = true;
	AutoRef<Data> data = new Data();
	FileSystem::getInstance()->getContentData(m_path, data);
	this->onLoad(data);
}

void Asset::unloadAsset()
{
	if (!m_loaded)return;
	this->onUnload();
	m_loaded = false;
}

END_OGS_NAMESPACE