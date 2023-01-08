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
		Vector3 center;   // �����������ĵ�
		Vector3 halfExtents; //����ߵ�һ��
		Matrix3 orientation; //�������
	};
}
END_OGS_NAMESPACE