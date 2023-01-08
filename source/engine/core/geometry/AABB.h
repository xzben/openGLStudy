#pragma once

#include "core/geometry/Shape.h"
#include "core/math/Vector3.h"

BEGIN_OGS_NAMESPACE

namespace Geometry
{
	class AABB : public Shape
	{
	public:
		AABB();

	public:
		Vector3 center;   // 本地坐标中心点
		Vector3 halfExtents; //长宽高的一半
	};
}
END_OGS_NAMESPACE