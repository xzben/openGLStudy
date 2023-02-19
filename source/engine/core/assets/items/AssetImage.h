#pragma once

#include "Asset.h"

BEGIN_OGS_NAMESPACE

class AssetImage : public Asset
{
	DECLARE_CLASS(AssetImage)
	DECLARE_REFLEX_CLASS_FIELD(AssetImage)
public:
	virtual void onLoad(const AutoRef<Data>& data)override;
	virtual void onUnload()override;

	const byte* getImageData() { return m_data; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	PixelFormat getFormat() { return m_format; }
protected:
	int m_width;
	int m_height;
	PixelFormat m_format{PixelFormat::RGBA8888};
	byte* m_data;
};

typedef AssetImage Image;

END_OGS_NAMESPACE