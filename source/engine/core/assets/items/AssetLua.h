#pragma once

#include "AssetText.h"

BEGIN_OGS_NAMESPACE

class AssetLua : public AssetText
{
	DECLARE_CLASS(AssetLua)
public:
	virtual void onLoad(const AutoRef<Data>& data)override;
	virtual void onUnload()override;
};

END_OGS_NAMESPACE