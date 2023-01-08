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
		memset(value, 0, sizeof(float) * 3);
	}

	Vector3(const Vector3& rhs)
	{
		memcpy(value, rhs.value, sizeof(float) * 3);
	}

	Vector3(float xx, float yy, float zz)
		: x(xx), y(yy), z(zz)
	{

	}

	Vector3 operator-(const Vector3& rhs) const
	{
		Vector3 r;
		r.x = x - rhs.x;
		r.y = y - rhs.y;
		r.z = z - rhs.z;

		return r;
	}

	void operator-(float v)
	{
		x -= v;
		y -= v;
		z -= v;
	}

	void operator+(float v)
	{
		x += v;
		y += v;
		z += v;
	}

	float length() const;
	float dot(const Vector3& rhs) const;
	Vector3 cross(const Vector3& rhs) const;
	void normalize();
};
END_OGS_NAMESPACE