#ifndef __FILE_UTILS_2021_09_06_H__
#define __FILE_UTILS_2021_09_06_H__

#include "common.h"
#include <string>

BEGIN_NAMESPACE

class Data {
	friend class FileUtils;
private:
	int m_bufSize;
	int m_contentSize;
	int m_writeOffset;
	byte* m_content;
protected:
	void setContentSize(int size) {
		this->m_contentSize = size;
	}
public:
	Data();
	~Data();
	Data(const byte* data, const int size);
	void resetSize(const int& size);
	void setData(const byte* data, const int size);


	byte* buffer() {
		return this->m_content;
	}

	byte* getContent() {
		return this->m_content;
	}
	const int& getContentSize() {
		return this->m_contentSize;
	}
};

class FileUtils {
public:
	std::vector<std::string> m_searchpaths;

	static FileUtils* getInstance() {
		static FileUtils s_instance;

		return &s_instance;
	}

	void addSearchPath(std::string path);

	bool getData(const std::string &filename, Data* data);
	std::string getString(const std::string &filename);
	std::string getfullpath(const std::string& filename);
};

END_NAMESPACE
#endif //__FILE_UTILS_2021_09_06_H__ 
