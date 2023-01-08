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
		Vector3 origin;   // �������
		Vector3 dir; //���߷���
	};
}
END_OGS_NAMESPACE