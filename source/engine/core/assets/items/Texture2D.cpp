#include "Texture2D.h"

BEGIN_OGS_NAMESPACE

IMPLEMENT_CLASS(Texture2D)

BEGIN_REFLEX_CLASS_FIELD(Texture2D)
END_REFLEX_CLASS_FIELD()

Texture2D::Texture2D()
{

}

Texture2D::~Texture2D()
{

}

void Texture2D::setImage(AssetImage* image)
{
	std::vector<AutoRef<AssetImage>> mipmaps;
	if (image != nullptr)
	{
		mipmaps.emplace_back(image);
	}
	setMipmaps(mipmaps);
}

void Texture2D::setMipmaps(std::vector<AutoRef<AssetImage>>& values)
{
	m_mipmaps = values;
	setMipmapLevel(m_mipmaps.size());

}

END_OGS_NAMESPACE