#pragma once

#include "define.h"
#include "core/base/Object.h"
#include "core/render/render_macro.h"
BEGIN_OGS_NAMESPACE

class RenderTexture : public Object
{
public:
	RenderTexture();

	void active();
protected:
	RenderHandle m_handle;
};
END_OGS_NAMESPACE