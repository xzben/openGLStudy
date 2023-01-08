/*
	��
*/
#pragma once

#include "core/geometry/Shape.h"
#include "core/math/Vector3.h"

BEGIN_OGS_NAMESPACE

namespace Geometry
{
	class Sphere : public Shape
	{
	public:
		Sphere();

	public:
		Vector3 center;   // �����������ĵ�
		Vector3 radius; //����ߵ�һ��
	};
}
END_OGS_NAMESPACE