#pragma once
#include "common.h"
#include "core/tool/Singleton.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "core/base/Object.h"
#include "Data.h"

BEGIN_OGS_NAMESPACE

class FileSystem : public Singleton<FileSystem>
{
public:
	FileSystem();
	~FileSystem();

	void addSearchPath(const std::string& path, bool front = false);
	void removeSearchPath(const std::string& path);
	const std::vector<std::string>& getSearchPaths() { return m_searchPaths; }
	void clearFileCache();

	std::string getFullPath(const std::string& path);
	bool isFileExists(const std::string& path);
	bool isDirectorExists(const std::string& path);
	bool rename(const std::string& from, const std::string& dest);
	bool remove(const std::string& path);
	bool createDirectories(const std::string& path);
	std::string getString(const std::string& path);
	bool getContentData(const std::string& path, Data* data);

private:
	std::vector<std::string> m_searchPaths;
	std::unordered_map<std::string, std::string> m_filecaches;
};

END_OGS_NAMESPACE