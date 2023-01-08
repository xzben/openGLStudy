#pragma once

#include "TextureBase.h"

BEGIN_OGS_NAMESPACE

class RenderTexture : public TextureBase
{
	DECLARE_CLASS(RenderTexture)
public:
	virtual void onLoad(const AutoRef<Data>& data)override;
	virtual void onUnload()override;
};

END_OGS_NAMESPACE