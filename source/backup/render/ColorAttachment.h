#pragma once

#include "core/render/GfxObject.h"
BEGIN_OGS_NAMESPACE

class ColorAttachment : public GfxObject
{
public:
	ColorAttachment();
	virtual ~ColorAttachment();

	virtual void handleInit() override;
};
END_OGS_NAMESPACE