#pragma once

#include "core/geometry/Shape.h"
#include "core/math/Vector3.h"
#include "core/math/Matrix3.h"

BEGIN_OGS_NAMESPACE

namespace Geometry
{
	class OOB : public Shape
	{
	public:
		OOB();
	public:
		Vector3 center;   // 本地坐标中心点
		Vector3 halfExtents; //长宽高的一半
		Matrix3 orientation; //方向矩阵
	};
}
END_OGS_NAMESPACE