#pragma once

#include "Asset.h"

BEGIN_OGS_NAMESPACE

class AssetImage : public Asset
{
	DECLARE_CLASS(AssetImage)
public:
	virtual void onLoad(const AutoRef<Data>& data)override;
	virtual void onUnload()override;
protected:
	int m_width;
	int m_height;
	int m_channel;
	byte* m_data;
};

END_OGS_NAMESPACE