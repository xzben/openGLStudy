#ifndef __2022_03_26_RENDER_DATA_H___
#define __2022_03_26_RENDER_DATA_H___

#include "base/Camera.h"
#include "light/Light.h"

BEGIN_NAMESPACE

struct RenderData
{
	Camera* mainCamera;
	Light*	mainLight;
};

END_NAMESPACE

#endif//__2022_03_26_RENDER_DATA_H___
