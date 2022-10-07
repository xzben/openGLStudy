#pragma once
#include "define.h"
#include "core/reflex/reflex.h"
BEGIN_OGS_NAMESPACE

class Vector3
{
	DECLARE_CLASS_BASE(Vector3)
	DECLARE_REFLEX_CLASS_FIELD(Vector3)
public:
	union
	{
		struct {
			float x, y, z;
		};

		struct {
			float r, g, b;
		};

		float value[3];
	};

	Vector3()
	{
		value[0] = value[1] = value[2] = 0;
	}

	Vector3(float xx, float yy, float zz)
		: x(xx), y(yy), z(zz)
	{

	}
};
END_OGS_NAMESPACE