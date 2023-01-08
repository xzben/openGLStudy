#pragma once

#include "SimpleTexture.h"

BEGIN_OGS_NAMESPACE

class AssetImage;

class Texture2D : public SimpleTexture
{
	DECLARE_CLASS(Texture2D)
	DECLARE_REFLEX_CLASS_FIELD(Texture2D)
public:
	Texture2D();
	virtual ~Texture2D();

	void setImage(AssetImage* image);
	void setMipmaps(std::vector<AutoRef<AssetImage>>& values);
protected:
	std::vector<AutoRef<AssetImage>> m_mipmaps;
	std::vector<std::string> m_mipmapUuids;
};
END_OGS_NAMESPACE