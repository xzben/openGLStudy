#pragma once

#include "common.h"
#include "core/base/Component.h"
#include "math/math.h"

BEGIN_OGS_NAMESPACE

class TransformComponent : public Component
{
public:
	TransformComponent();
private:
	Position m_pos{0,0,0};
	Rotation m_rotation{0,0,0};
	Scale    m_scale{1,1,1};
};

END_OGS_NAMESPACE