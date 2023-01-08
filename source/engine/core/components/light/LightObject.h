#pragma once

#include "common.h"
#include "core/base/Object.h"
#include "core/render/render_macro.h"
#include "core/math//math.h"
#include "core/base/Component.h"
BEGIN_OGS_NAMESPACE

class LightObject : public Component
{
	DECLARE_CLASS(LightObject)
public:
	LightObject();
private:
	LightType m_type;
	Color m_lightColor;
};
END_OGS_NAMESPACE