/*
	������
*/
#pragma once

#include "core/geometry/Shape.h"
#include "core/math/Vector3.h"
#include "core/math/Quaterion.h"
#include "core/math/Axis.h"

BEGIN_OGS_NAMESPACE

namespace Geometry
{
	class Capsule : public Shape
	{
	public:
		Capsule(float radius = 0.5, float halfHeight = 0.5, Math::Axis axis = Math::Axis::Y);
	public:
		float radius;   // �������򲿰뾶
		float halfHeight; //���������ĵ����Բ�ĵľ��롣
		Math::Axis   axis; //������ı��س���ӳ���ϵ [0,1,2] => [x,y,z]��
		Vector3 center; //�������ԭ�㡣
		Vector3 ellipseCenter0; // cache, local center of ellipse
		Vector3 ellipseCenter1; //cache, local center of ellipse
		Quaterion rotation; //���������ת��
	};
}
END_OGS_NAMESPACE