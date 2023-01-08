#pragma once

#include "common.h"
#include "core/base/Object.h"
#include "render_macro.h"

BEGIN_OGS_NAMESPACE

class GfxObject : public Object
{
	DECLARE_RUNTIME_CLASS(GfxObject)
public:
	RenderHandle getHandle() { return m_handle; }
protected:
	RenderHandle m_handle{ INVALID_HANDLE };
};
END_OGS_NAMESPACE