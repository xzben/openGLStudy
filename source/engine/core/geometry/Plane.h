#pragma once

#include "core/math/Vector3.h"
#include "core/geometry/Shape.h"
BEGIN_OGS_NAMESPACE
namespace Geometry
{
	class Plane : public Shape
	{
	public:
		Plane();
	public:
		Vector3 normal; //法线
		float   dist; // 原点到平面的距离
	};
}
END_OGS_NAMESPACE

