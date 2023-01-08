/*
	胶囊体
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
		float radius;   // 胶囊体球部半径
		float halfHeight; //胶囊体中心点和球部圆心的距离。
		Math::Axis   axis; //胶囊体的本地朝向，映射关系 [0,1,2] => [x,y,z]。
		Vector3 center; //胶囊体的原点。
		Vector3 ellipseCenter0; // cache, local center of ellipse
		Vector3 ellipseCenter1; //cache, local center of ellipse
		Quaterion rotation; //胶囊体的旋转。
	};
}
END_OGS_NAMESPACE