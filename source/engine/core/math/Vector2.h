#pragma once
#include "define.h"
#include "core/reflex/reflex.h"
BEGIN_OGS_NAMESPACE

class Vector2
{
	DECLARE_CLASS_BASE(Vector2)
	DECLARE_REFLEX_CLASS_FIELD(Vector2)
public:
	union
	{
		struct {
			float x, y;
		};

		float value[2];
	};

	Vector2()
	{
		memset(value, 0, sizeof(float) * 2);
	}

	Vector2(const Vector2& rhs)
	{
		memcpy(value, rhs.value, sizeof(float) * 2);
	}

	Vector2(float xx, float yy)
		: x(xx), y(yy)
	{

	}

	Vector2 operator-(const Vector2& rhs) const
	{
		Vector2 r;
		r.x = x - rhs.x;
		r.y = y - rhs.y;

		return r;
	}

	void operator-(float v)
	{
		x -= v;
		y -= v;
	}

	void operator+(float v)
	{
		x += v;
		y += v;
	}

	float length() const;
	float dot(const Vector2& rhs) const;
	float cross(const Vector2& rhs) const;
	void normalize();
};
END_OGS_NAMESPACE