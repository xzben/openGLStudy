#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include "Image.h"
#include <glad/glad.h>

Image::Image(const std::string& filename) 
	:Image()
{
	this->loadImage(filename);
}

Image::Image() 
	: m_texture(0),
	m_width(0),
	m_height(0),
	m_filename(""),
	m_channels(0),
	m_imageType(IMAGE_TYPE::UNKNOW)
{
	glGenTextures(1, &this->m_texture);
	
}

Image::~Image() {

}

void Image::render() {
	glBindTexture(GL_TEXTURE_2D, this->m_texture);
}

static Image::IMAGE_TYPE getImageType(byte* buf, const int& len) {
	stbi__context s;
	stbi__start_mem(&s, buf, len);

	if (stbi__png_test(&s)) {
		return Image::IMAGE_TYPE::PNG;
	}

	if (stbi__jpeg_test(&s)) {
		return Image::IMAGE_TYPE::JPEG;
	}

	return Image::IMAGE_TYPE::UNKNOW;
}

bool Image::loadImage(const std::string& filename) {
	if (!FileUtils::getInstance()->getData(filename, &this->m_data))
		return false;

	stbi_set_flip_vertically_on_load(true);
	this->m_imageType = getImageType(this->m_data.getContent(), this->m_data.getContentSize());

	unsigned char *data = stbi_load_from_memory(this->m_data.getContent(),
		this->m_data.getContentSize(),
		&this->m_width,
		&this->m_height, 
		&this->m_channels, 
		0);

	if (data) {
		glBindTexture(GL_TEXTURE_2D, this->m_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		switch (this->m_imageType)
		{
		case IMAGE_TYPE::PNG:
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_width, this->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			break;
		}
		case IMAGE_TYPE::JPEG:
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_width, this->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			break;
		}
		}
		
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		return true;
	}

	return false;
}