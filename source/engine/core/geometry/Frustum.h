#pragma once

#include "core/geometry/Plane.h"
#include "core/math/Vector3.h"
#include <vector>

BEGIN_OGS_NAMESPACE

namespace Geometry
{
	class Frustum : public Shape
	{
	public:
		Frustum();
	public:
		std::vector<Vector3> vertices;
		std::vector<Plane>   planes;
	};
}

END_OGS_NAMESPACE

