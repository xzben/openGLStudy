#pragma once

#include "AssetText.h"

BEGIN_OGS_NAMESPACE

class AssetShader : public AssetText
{
	DECLARE_CLASS(AssetShader)
public:
	virtual void onLoad(const AutoRef<Data>& data)override;
	virtual void onUnload()override;
};

END_OGS_NAMESPACE