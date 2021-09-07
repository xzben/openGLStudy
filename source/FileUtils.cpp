#include "FileUtils.h"
#include "GLFW/glfw3.h"
#include <fstream>
#include <sstream>
#include <iostream>

#define BUFFER_SIZE_BLOCK  1024

Data::Data() 
	: m_content(nullptr),
	m_bufSize(0),
	m_contentSize(0),
	m_writeOffset(0)
{

}

Data::Data(const byte* data, const int size)
{
	this->setData(data, size);
}

Data::~Data() 
{
	if (this->m_content != nullptr) {
		delete this->m_content;
		this->m_content = nullptr;
		this->m_bufSize = 0;
		this->m_contentSize = 0;
	}
}

void Data::resetSize(const int& size)
{
	int newSize = BUFFER_SIZE_BLOCK;
	if (this->m_bufSize > newSize)
		newSize = this->m_bufSize;

	while (newSize < size) {
		newSize *= 2;
	}

	if (newSize != this->m_bufSize) {
		this->m_bufSize = newSize;
		byte* oldData = this->m_content;
		this->m_content = new byte[newSize];
		memset(this->m_content, 0, newSize);
		memcpy(this->m_content, oldData, this->m_contentSize);
		delete oldData;
	}
}

void Data::setData(const byte* data, const int size) {
	this->resetSize(size);
	memcpy((void*)(this->m_content), data, size);
}

std::string FileUtils::getString(const std::string &filename)
{
	Data data;
	this->getData(filename, &data);

	return (char*)data.getContent();
}

bool FileUtils::getData(const std::string &filename, Data* data) {
	std::string fullpath = this->getfullpath(filename);
	std::string content;
	std::ifstream file;

	FILE *fp = fopen(fullpath.c_str(), "rb");
	if (!fp)
		return false;
#if defined(_MSC_VER)
	auto descriptor = _fileno(fp);
#else
	auto descriptor = fileno(fp);
#endif
	struct stat statBuf;
	if (fstat(descriptor, &statBuf) == -1) {
		fclose(fp);
		return false;
	}
	size_t size = statBuf.st_size;
	data->resetSize(size);
	size_t readsize = fread(data->buffer(), 1, size, fp);
	fclose(fp);

	return true;
}

std::string FileUtils::getfullpath(const std::string& filename)
{
	return "../../Resources/"+filename;
}