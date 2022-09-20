#pragma once

#include "common.h"
#include "core/base/Component.h"

BEGIN_OGS_NAMESPACE

class Camera : public Component
{
	DECLARE_CLASS(Camera)
public:
	Camera();
};

END_OGS_NAMESPACE