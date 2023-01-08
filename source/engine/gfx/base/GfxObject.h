#pragma once

#include "common.h"
#include "gfx/base/gfx_base_define.h"
#include "core/base/Object.h"
#include "Attribute.h"
#include "Uniform.h"

BEGIN_OGS_GFX_NAMESPACE

class GfxObject : public Object
{
	DECLARE_RUNTIME_CLASS(GfxObject)
public:
	GfxObject(ObjectType type) :m_type(type) {};

protected:
	ObjectType m_type;
};
END_OGS_GFX_NAMESPACE