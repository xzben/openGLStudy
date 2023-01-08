#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>

#include "AssetImage.h"
#include "core/filesystem/Data.h"

BEGIN_OGS_NAMESPACE

IMPLEMENT_CLASS(AssetImage)

void AssetImage::onLoad(const AutoRef<Data>& data)
{
	int channel;
	m_data = stbi_load_from_memory(data->getData(), data->getSize(), &m_width, &m_height, &channel, 0);
	switch (channel)
	{
	case 3:
	{
		m_format = PixelFormat::RGB888;
		break;
	}
	case 4:
	{
		m_format = PixelFormat::RGBA8888;
		break;
	}
	default:
	{
		ASSERT(false, "channel num[%d] is not support", channel);
		break;
	}
	}
}

void AssetImage::onUnload()
{
	stbi_image_free(m_data);
}

END_OGS_NAMESPACE