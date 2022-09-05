#include "FileSystem.h"
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
BEGIN_OGS_NAMESPACE

namespace fs = std::filesystem;

FileSystem::FileSystem()
{

}

FileSystem::~FileSystem()
{

}

void FileSystem::addSearchPath(const std::string& path, bool front /*= false */)
{
	if (front)
	{
		m_searchPaths.insert(m_searchPaths.begin(), path);
	}
	else
	{
		m_searchPaths.push_back(path);
	}
}
void FileSystem::removeSearchPath(const std::string& path)
{
	for (auto it = m_searchPaths.begin(); it != m_searchPaths.end(); )
	{
		if (*it == path)
		{
			it = m_searchPaths.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void FileSystem::clearFileCache()
{
	m_filecaches.clear();
}

std::string FileSystem::getFullPath(const std::string& path)
{
	fs::path temppath(path);
	if (temppath.is_absolute())
		return path;

	auto it = m_filecaches.find(path);
	if ( it != m_filecaches.end())
	{
		return it->second;
	}

	for (auto it = m_searchPaths.begin(); it != m_searchPaths.end(); it++)
	{
		std::string fullpath = *it + "/" + path;
		if (fs::exists(fullpath))
		{
			m_filecaches.insert(std::make_pair(path, fullpath));
			return fullpath;
		}
	}

	return "";
}

bool FileSystem::isFileExists(const std::string& path)
{
	std::string fullpath = getFullPath(path);

	return fullpath != "";
}

bool FileSystem::rename(const std::string& from, const std::string& dest)
{
	if (!isFileExists(from)) return false;
	if (isFileExists(dest)) return false;

	fs::rename(from, dest);
	
	return true;
}

bool FileSystem::remove(const std::string& path)
{
	return fs::remove_all(getFullPath(path));
}

bool FileSystem::createDirectories(const std::string& path)
{
	return fs::create_directories(path);
}

std::string FileSystem::getString(const std::string& path)
{
	Data data;
	if (!getContentData(path, &data))
		return "";
	
	return (char*)data.getData();
}

bool FileSystem::getContentData(const std::string& path, Data* data)
{
	if (!isFileExists(path)) false;

	std::string fullpath = getFullPath(path);
	FILE* fp = fopen(fullpath.c_str(), "rb");
	if (!fp)
		return false;
	
#if defined(_MSC_VER)
	int descriptor = _fileno(fp);
#else
	int descriptor = fileno(fp);
#endif

	struct stat statBuf;
	if (fstat(descriptor, &statBuf) == -1) {
		fclose(fp);
		return false;
	}

	size_t size = statBuf.st_size;
	data->reverse(size);
	size_t readsize = fread(data->getData(), 1, size, fp);
	fclose(fp);
	data->writeOffset(readsize);

	return true;
}

END_OGS_NAMESPACE