#pragma once

#include "define.h"

BEGIN_OGS_NAMESPACE
namespace Geometry
{
	enum GeometryType
	{
		SHAPE_RAY = 1 << 0,
		SHAPE_LINE = 1 << 1,
		SHAPE_SPHERE = 1 << 2,
		SHAPE_AABB = 1 << 3,
		SHAPE_OBB = 1 << 4,
		SHAPE_PLANE = 1 << 5,
		SHAPE_TRIANGLE = 1 << 6,
		SHAPE_FRUSTUM = 1 << 7,
		SHAPE_FRUSTUM_ACCURATE = 1 << 8,
		SHAPE_CAPSULE = 1 << 9,
		SHAPE_SPLINE = 1 << 10,
	};

	class Shape
	{
	public:
		GeometryType type;
	};
}
END_OGS_NAMESPACE