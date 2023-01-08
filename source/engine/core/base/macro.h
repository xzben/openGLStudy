#pragma once

#include "define.h"

BEGIN_OGS_NAMESPACE

enum Layers : unsigned int
{
	NONE = 0,
	IGNORE_RAYCAST = (1 << 20),
	
	GIZMOS =(1 << 21),
	EDITOR = (1 << 22),
	UI_3D = (1 << 23),
	SCENE_GIZMO = (1 << 24),
	UI_2D = (1 << 25),

	PROFILER = (1 << 28),
	DEFAULT = (1 << 30),

	ALL = 0xffffffff,
};

const uint32 CAMERA_DEFAUK_MASK = Layers::UI_2D | Layers::GIZMOS | Layers::EDITOR | Layers::SCENE_GIZMO | Layers::PROFILER;

END_OGS_NAMESPACE