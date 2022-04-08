#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include "Texture.h"
#include <glad/glad.h>

BEGIN_NAMESPACE

Texture::Texture() 
	: m_texture(0)
{
	glGenTextures(1, &m_texture);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
	m_texture = 0;
}

static IMAGE_TYPE getImageType(byte* buf, const int& len) {
	stbi__context s;
	stbi__start_mem(&s, buf, len);

	if (stbi__png_test(&s)) {
		return IMAGE_TYPE::PNG;
	}

	if (stbi__jpeg_test(&s)) {
		return IMAGE_TYPE::JPEG;
	}

	if (stbi__tga_test(&s)) {
		return IMAGE_TYPE::TGA;
	}

	return IMAGE_TYPE::UNKNOW;
}

bool Texture::initAttachment(float width, float height)
{
	this->m_width = width;
	this->m_height = height;
	glBindTexture(GL_TEXTURE_2D, m_texture);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

bool Texture::init(const std::string filename)
{
	Data data;
	if (!FileUtils::getInstance()->getData(filename, &data))
		return false;

	stbi_set_flip_vertically_on_load(true);
	this->m_imageType = getImageType(data.getContent(), data.getContentSize());

	unsigned char* img_data = stbi_load_from_memory(data.getContent(),
		data.getContentSize(),
		&this->m_width,
		&this->m_height,
		&this->m_channels,
		0);

	if (img_data == nullptr)
		return false;

	//��������ʼ�����������
	glBindTexture(GL_TEXTURE_2D, m_texture);
	

	//���������Ʒ�ʽ������ߴ�Ϊ 0 - 1 ���������ߴ� 1 ʱ���ȡֵ���
	// REPEAT �����ظ��ķ�ʽ 0 - 1 0- 1 ���ظ�
	// MIRRORDER_REPEAT �����ظ�  0 - 1 1 - 0 0 - 1 �����ظ�
	// CLAMP_TO_EDGE ʹ�ñ�Ե����
	// CLAMP_TO_BORDER ʹ��ָ����ɫ���
	switch (this->m_wrap)
	{
	case TEXTURE_WRAP::REPEAT:
	{
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //���� x �᷽������Ļ��Ʒ�ʽΪ  REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //���� y �᷽������Ļ��Ʒ�ʽΪ  REPEAT
		break;
	}
	case TEXTURE_WRAP::MIRRORED_REPEAT:
	{

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); //���� x �᷽������Ļ��Ʒ�ʽΪ  REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); //���� y �᷽������Ļ��Ʒ�ʽΪ  REPEAT
		break;
	}
	case TEXTURE_WRAP::CLAMP_TO_EDGE:
	{

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //���� x �᷽������Ļ��Ʒ�ʽΪ  REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //���� y �᷽������Ļ��Ʒ�ʽΪ  REPEAT
		break;
	}
	case TEXTURE_WRAP::CLAMP_TO_BORDER:
	{

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); //���� x �᷽������Ļ��Ʒ�ʽΪ  REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); //���� y �᷽������Ļ��Ʒ�ʽΪ  REPEAT
		break;
	}
	}

	//��������Ĺ��˷�ʽ����Ҫ������������ʱ���������ص�ȡֵ�ķ�ʽ
	// linear ��������ȡֵ���ᰴ���ٽ�����ֵȡ���Բ�ֵ
	// nearst �����ٽ�ȡֵ����ȡ�����ٽ�������ֵ
	// ������Сʱ�Ĺ��˷�ʽ
	// ��Сʱ �ȷŴ���˶༶��Զ����
	switch (this->m_minFilter)
	{
	case TEXTURE_FILTER::LINEAR:
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			break;
		}
	case TEXTURE_FILTER::NEAREST:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;
	}
	case TEXTURE_FILTER::LINEAR_MIPMAP_LINEAR:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;
	}
	case TEXTURE_FILTER::LINEAR_MIPMAP_NEAREST:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		break;
	}
	case TEXTURE_FILTER::NEAREST_MIPMAP_LINEAR:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		break;
	}
	case TEXTURE_FILTER::NEAREST_MIPMAP_NEAREST:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		break;
	}
	}

	//��������Ĺ��˷�ʽ����Ҫ������������ʱ���������ص�ȡֵ�ķ�ʽ
	// linear ��������ȡֵ���ᰴ���ٽ�����ֵȡ���Բ�ֵ
	// nearst �����ٽ�ȡֵ����ȡ�����ٽ�������ֵ
	// ���÷Ŵ�ʱ�Ĺ��˷�ʽ
	switch (this->m_magFilter)
	{
	case TEXTURE_FILTER::LINEAR:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	}
	case TEXTURE_FILTER::NEAREST:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	}
	}

	switch (this->m_imageType)
	{
	case IMAGE_TYPE::PNG:
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_width, this->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
		break;
	}
	case IMAGE_TYPE::JPEG:
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_width, this->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
		break;
	}
	}

	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(img_data);

	return true;
}

void Texture::use(int index)
{
	CC_ASSERT(index >= 0 && index <= 31);

	m_useIndex = index;
	//��������index
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, this->m_texture);
}

void Texture::unuse()
{
	glActiveTexture(GL_TEXTURE0 + m_useIndex);
	glBindTexture(GL_TEXTURE_2D, 0);
}

END_NAMESPACE