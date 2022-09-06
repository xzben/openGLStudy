#pragma once

#include "Asset.h"

BEGIN_OGS_NAMESPACE

class AssetMaterial : public Asset
{
	DECLARE_CLASS(AssetMaterial)
public:
	virtual void onLoad(SharePtr<Data>& data)override;
	virtual void onUnload()override;
protected:
};

END_OGS_NAMESPACE