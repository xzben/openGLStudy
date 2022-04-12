#ifndef __2022_01_05_TEXTURE_H__
#define __2022_01_05_TEXTURE_H__

#include "common.h"
#include "render/config.h"
#include "base/Object.h"
#include "utils/FileUtils.h"
#include "base/NonCopyable.h"

BEGIN_NAMESPACE

class Texture : public Object, public NonCopyable
{
protected:
	friend class FrameBuffer;

	TEXTURE_HANDLE m_texture;
	std::string m_filename;
	int m_width;
	int m_height;
	int m_channels;
	IMAGE_TYPE m_imageType;
	TEXTURE_WRAP m_wrap = TEXTURE_WRAP::REPEAT;
	TEXTURE_FILTER m_minFilter = TEXTURE_FILTER::NEAREST_MIPMAP_NEAREST;
	TEXTURE_FILTER m_magFilter = TEXTURE_FILTER::LINEAR;
	int  m_useIndex;
public:
	Texture();
	virtual ~Texture();
	void setWrap(TEXTURE_WRAP wrap) { this->m_wrap = wrap;  }
	void setFilter(TEXTURE_FILTER minFilter, TEXTURE_FILTER magFilter) { 
		this->m_minFilter = minFilter; 
		this->m_magFilter = magFilter;
	}
	bool init(const std::string filename);
	bool initAttachment(float width, float height);
	bool initDepthStencilAttachment(float width, float height);

	virtual void use(int index = 0);
	virtual void unuse();

	int getWidth() { return this->m_width; }
	int getHeight() { return this->m_height; }
	int getChannels() { return this->m_channels; }
};

struct SubTexture
{
	std::string name;
	Texture* tex;
};

END_NAMESPACE
#endif//__2022_01_05_TEXTURE_H__