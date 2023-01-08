#include "Texture.h"
#include "core/base/GameApp.h"
#include "core/view/GameView.h"
#include "core/filesystem/Data.h"
#include "core/view/Screen.h"
#include "core/assets/AssetsMgr.h"
#include "core/assets/items/AssetImage.h"

BEGIN_OGS_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(Texture)

Texture* Texture::createAttatchColor(Size* size /*= nullptr*/)
{
	Texture* tex = new Texture;
	tex->initWithColorAttachment(size);
	return tex;
}

Texture::Texture()
{
	glGenTextures(1, &m_handle);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_handle);
	m_handle = INVALID_HANDLE;
}

void Texture::setSize(const Size& size)
{
	m_size = size;
	updateData();
}

bool Texture::initWithFile(const std::string& filename)
{
	AssetImage* img = AssetsMgr::getInstance()->getAsset<AssetImage>(filename, true);
	return initWithImageData(img);
}

bool Texture::initWithImageData(AssetImage* image)
{
	if (image == nullptr) return false;
	m_image = image;
	m_size.width = m_image->m_width;
	m_size.height = m_image->m_height;
	switch (m_image->m_channel)
	{
	case 1: { m_format = TextureFormat::R8;    break; }
	case 2: { m_format = TextureFormat::RG8;   break; }
	case 3: { m_format = TextureFormat::RGB8;  break; }
	case 4: { m_format = TextureFormat::RGBA8; break; }
	}
	updateData();
	updateSampeInfo();

	return true;
}

void Texture::initWithColorAttachment(Size* psize /*= nullptr*/)
{
	m_size = psize == nullptr ? Screen::getSize() : *psize;
	m_sampeinfo = SampleInfo::DefaultColorAttachment;
	m_usage = TextureUsage::COLOR_ATTACHMENT;

	glBindTexture(GL_TEXTURE_2D, m_handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.width, m_size.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	updateSampeInfo();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::initWithDepth24Stencil8Attachment(Size* psize /*= nullptr*/)
{
	m_size = psize == nullptr ? Screen::getSize() : *psize;
	m_sampeinfo = SampleInfo::DefaultDepthStencilAttachment;
	m_usage = TextureUsage::DEPTH_STENCIL_ATTACHMENT;

	glBindTexture(GL_TEXTURE_2D, m_handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_size.width, m_size.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
	updateSampeInfo();
}

void Texture::updateSampeInfo()
{
	glBindTexture(GL_TEXTURE_2D, m_handle);
	switch (m_sampeinfo.wrap)
	{
	case TextureWrap::REPEAT:
	{

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //设置 x 轴方向纹理的环绕方式为  REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //设置 y 轴方向纹理的环绕方式为  REPEAT
		break;
	}
	case TextureWrap::MIRRORED_REPEAT:
	{

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); //设置 x 轴方向纹理的环绕方式为  REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); //设置 y 轴方向纹理的环绕方式为  REPEAT
		break;
	}
	case TextureWrap::CLAMP_TO_EDGE:
	{

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //设置 x 轴方向纹理的环绕方式为  REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //设置 y 轴方向纹理的环绕方式为  REPEAT
		break;
	}
	case TextureWrap::CLAMP_TO_BORDER:
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
	switch (m_sampeinfo.filterMin)
	{
	case TextureFilter::LINEAR:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		break;
	}
	case TextureFilter::NEAREST:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;
	}
	case TextureFilter::LINEAR_MIPMAP_LINEAR:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;
	}
	case TextureFilter::LINEAR_MIPMAP_NEAREST:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		break;
	}
	case TextureFilter::NEAREST_MIPMAP_LINEAR:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		break;
	}
	case TextureFilter::NEAREST_MIPMAP_NEAREST:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		break;
	}
	}

	//设置纹理的过滤方式，主要控制纹理缩放时候，两个像素点取值的方式
	// linear 代表线性取值，会按照临近像素值取线性插值
	// nearst 代表临近取值，会取像素临近的像素值
	// 设置放大时的过滤方式
	switch (m_sampeinfo.filterMag)
	{
	case TextureFilter::LINEAR:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	}
	case TextureFilter::NEAREST:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	}
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::updateData()
{
	const void* data = m_image.get() == nullptr ? NULL : m_image->getImageData();

	glBindTexture(GL_TEXTURE_2D, m_handle);
	int glfmt = GL_RGBA;
	switch (m_format)
	{
	case OGS::TextureFormat::A8:
	{
		glfmt = GL_ALPHA;
		break;
	}
	case OGS::TextureFormat::R8:
	{
		glfmt = GL_RED;
		break;
	}
	case OGS::TextureFormat::G8:
	{
		glfmt = GL_GREEN;
		break;
	}
	case OGS::TextureFormat::B8:
	{
		glfmt = GL_BLUE;
		break;
	}
	case OGS::TextureFormat::RGB8:
	{
		glfmt = GL_RGB;
		break;
	}
	case OGS::TextureFormat::RGBA8:
	{
		glfmt = GL_RGBA;
		break;
	}
	}
	glTexImage2D(GL_TEXTURE_2D, 0, glfmt, m_size.width, m_size.height, 0, glfmt, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
}
END_OGS_NAMESPACE