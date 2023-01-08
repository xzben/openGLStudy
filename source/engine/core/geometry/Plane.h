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
		Vector3 normal; //����
		float   dist; // ԭ�㵽ƽ��ľ���
	};
}
END_OGS_NAMESPACE

