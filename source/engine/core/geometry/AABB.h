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
		Vector3 center;   // �����������ĵ�
		Vector3 halfExtents; //����ߵ�һ��
	};
}
END_OGS_NAMESPACE