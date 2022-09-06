#pragma once

#include "Asset.h"

BEGIN_OGS_NAMESPACE

class AssetText : public Asset
{
	DECLARE_CLASS(AssetText)
public:
	virtual void onLoad(SharePtr<Data>& data)override;
	virtual void onUnload()override;
	const std::string& getContent() { return m_content; }
protected:
	std::string m_content;
};

END_OGS_NAMESPACE