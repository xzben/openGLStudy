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

	//绑定纹理，开始设置纹理参数
	glBindTexture(GL_TEXTURE_2D, m_texture);
	

	//设置纹理环绕方式，纹理尺寸为 0 - 1 当初超出尺寸 1 时如何取值填充
	// REPEAT 就是重复的方式 0 - 1 0- 1 的重复
	// MIRRORDER_REPEAT 镜像重复  0 - 1 1 - 0 0 - 1 这种重复
	// CLAMP_TO_EDGE 使用边缘像素
	// CLAMP_TO_BORDER 使用指定颜色填充
	switch (this->m_wrap)
	{
	case TEXTURE_WRAP::REPEAT:
	{
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //设置 x 轴方向纹理的环绕方式为  REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //设置 y 轴方向纹理的环绕方式为  REPEAT
		break;
	}
	case TEXTURE_WRAP::MIRRORED_REPEAT:
	{

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); //设置 x 轴方向纹理的环绕方式为  REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); //设置 y 轴方向纹理的环绕方式为  REPEAT
		break;
	}
	case TEXTURE_WRAP::CLAMP_TO_EDGE:
	{

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //设置 x 轴方向纹理的环绕方式为  REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //设置 y 轴方向纹理的环绕方式为  REPEAT
		break;
	}
	case TEXTURE_WRAP::CLAMP_TO_BORDER:
	{

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); //设置 x 轴方向纹理的环绕方式为  REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); //设置 y 轴方向纹理的环绕方式为  REPEAT
		break;
	}
	}

	//设置纹理的过滤方式，主要控制纹理缩放时候，两个像素点取值的方式
	// linear 代表线性取值，会按照临近像素值取线性插值
	// nearst 代表临近取值，会取像素临近的像素值
	// 设置缩小时的过滤方式
	// 缩小时 比放大多了多级渐远设置
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

	//设置纹理的过滤方式，主要控制纹理缩放时候，两个像素点取值的方式
	// linear 代表线性取值，会按照临近像素值取线性插值
	// nearst 代表临近取值，会取像素临近的像素值
	// 设置放大时的过滤方式
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
	//设置纹理index
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, this->m_texture);
}

void Texture::unuse()
{
	glActiveTexture(GL_TEXTURE0 + m_useIndex);
	glBindTexture(GL_TEXTURE_2D, 0);
}

END_NAMESPACE