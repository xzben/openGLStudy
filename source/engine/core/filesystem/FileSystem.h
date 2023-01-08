#pragma once
#include "common.h"
#include "core/tool/Singleton.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "core/base/System.h"
#include "core/systems/InputSystem.h"

BEGIN_OGS_NAMESPACE

class Data;

class FileSystem : public System, public Singleton<FileSystem>
{
	DECLARE_RUNTIME_CLASS(FileSystem)
protected:
	friend class Singleton<FileSystem>;
	FileSystem();
public:
	~FileSystem();

	void addSearchPath(const std::string& path, bool front = false);
	void removeSearchPath(const std::string& path);
	const std::vector<std::string>& getSearchPaths() { return m_searchPaths; }
	void clearFileCache();

	std::string getFullPath(const std::string& path);
	bool isFileExists(const std::string& path);
	bool isDirectory(const std::string& path);
	bool isDirectoryExists(const std::string& path);
	bool rename(const std::string& from, const std::string& dest);
	bool remove(const std::string& path);
	bool createDirectories(const std::string& path);
	std::string getString(const std::string& path);
	bool getContentData(const std::string& path, const AutoRef<Data>& data);
	
	bool getDirectoryContents(const std::string& path, std::vector<std::string>& files, std::vector<std::string>& directories, bool recursive = false);
	bool getDirectoryFiles(const std::string& path, std::vector<std::string>& files, bool recursive = false, bool filterDirectory = true);
	//获取文件的文件名部分
	std::string getFilename(const std::string& filepath);
	//获取path 去除文件名字的 path 部分
	std::string getPath(const std::string& filepath);
	//获取文件的后缀名字
	std::string getFileExt(const std::string& filepath);

	bool writeString(const std::string& fullpath, const std::string& content);
	bool writeData(const std::string& fullpath, const AutoRef<Data>& data);
private:
	std::vector<std::string> m_searchPaths;
	std::unordered_map<std::string, std::string> m_filecaches;
};

END_OGS_NAMESPACE