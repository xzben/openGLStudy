#pragma once

#include "AssetText.h"

BEGIN_OGS_NAMESPACE

class AssetJson : public AssetText
{
	DECLARE_CLASS(AssetJson)
public:
	virtual void onLoad(const AutoRef<Data>& data)override;
	virtual void onUnload()override;
protected:
	JSON m_json;
};

END_OGS_NAMESPACE