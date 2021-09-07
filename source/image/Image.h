#ifndef __IMAGE_2021_09_07_H__
#define __IMAGE_2021_09_07_H__

#include <string>
#include "FileUtils.h"
#include "base/RenderNode.h"

class Image : public RenderNode {
public:
	enum IMAGE_TYPE {
		PNG,
		JPEG,
		UNKNOW,
	};
protected:
	uint m_texture;
	std::string m_filename;
	int m_width;
	int m_height;
	int m_channels;
	Data m_data;
	IMAGE_TYPE m_imageType;
public:
	virtual void render();
	Image(const std::string& filename);
	Image();
	~Image();
	bool loadImage(const std::string& filename);

	int getWidth() {
		return this->m_width;
	}
	int getHeight() {
		return this->m_height;
	}

	int getChannels() {
		return this->m_channels;
	}

	const byte* getData() {
		return this->m_data.getContent();
	}
};
#endif//__IMAGE_2021_09_07_H__