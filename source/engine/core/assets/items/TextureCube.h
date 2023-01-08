#pragma once

#include "SimpleTexture.h"

BEGIN_OGS_NAMESPACE

class TextureCube : public SimpleTexture
{
	DECLARE_CLASS(TextureCube)
	DECLARE_REFLEX_CLASS_FIELD(TextureCube)
public:
	TextureCube();
	virtual ~TextureCube();
};
END_OGS_NAMESPACE