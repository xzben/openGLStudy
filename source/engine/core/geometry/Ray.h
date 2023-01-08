#pragma once

#include "core/geometry/Shape.h"
#include "core/math/Vector3.h"

BEGIN_OGS_NAMESPACE

namespace Geometry
{
	class Ray : public Shape
	{
	public:
		Ray();
	public:
		Vector3 origin;   // 射线起点
		Vector3 dir; //射线方向
	};
}
END_OGS_NAMESPACE