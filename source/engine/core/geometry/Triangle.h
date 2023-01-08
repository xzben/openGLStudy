#pragma once

#include "core/geometry/Shape.h"
#include "core/math/Vector3.h"

BEGIN_OGS_NAMESPACE

namespace Geometry
{
	class Triangle : public Shape
	{
	public:
		Triangle();
	public:
		union
		{
			Vector3 pos[3];
			struct
			{
				Vector3 a;
				Vector3 b;
				Vector3 c;
			};
		};
	};
}
END_OGS_NAMESPACE