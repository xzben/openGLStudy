#pragma once

#include "Asset.h"

BEGIN_OGS_NAMESPACE

class AssetModel : public Asset
{
	DECLARE_CLASS(AssetModel)
public:
	virtual void onLoad(const AutoRef<Data>& data)override;
	virtual void onUnload()override;
protected:
	
};

END_OGS_NAMESPACE