#pragma once
#include "define.h"
#include "core/reflex/reflex.h"
BEGIN_OGS_NAMESPACE

class Vector4
{
	DECLARE_CLASS_BASE(Vector4)
	DECLARE_REFLEX_CLASS_FIELD(Vector4)
public:
	union
	{
		struct {
			float x, y, z, w;
		};

		struct {
			float r, g, b, a;
		};

		float value[4];
	};

	Vector4()
	{
		memset(value, 0, sizeof(float) * 3);
	}

	Vector4(const Vector4& rhs)
	{
		memcpy(value, rhs.value, sizeof(float) * 3);
	}

	Vector4(float xx, float yy, float zz, float ww)
		: x(xx), y(yy), z(zz), w(ww)
	{

	}

	Vector4 operator-(const Vector4& rhs) const
	{
		Vector4 r;
		for (int i = 0; i < 4; i++)
		{
			r.value[i] = value[i] - rhs.value[i];
		}
		return r;
	}

	void operator-(float v)
	{
		for (int i = 0; i < 4; i++)
		{
			value[i] -= v;
		}
	}

	void operator+(float v)
	{
		for (int i = 0; i < 4; i++)
		{
			value[i] += v;
		}
	}
};
END_OGS_NAMESPACE