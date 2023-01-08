#include "Vector2.h"
#include <cmath>

BEGIN_OGS_NAMESPACE

IMPLEMENT_CLASS_BASE(Vector2)

BEGIN_REFLEX_CLASS_FIELD(Vector2)
REFLEX_FIELD(float, x)
REFLEX_FIELD(float, y)
END_REFLEX_CLASS_FIELD()

float Vector2::length() const
{
	return std::sqrt(x * x + y * y);
}

void Vector2::normalize()
{
	float n = x * x + y * y;
	if (n == 1.f || n == 0.f) return;

	n = std::sqrt(n);

	n = 1.0f / n;
	x *= n;
	y *= n;
}

float Vector2::dot(const Vector2& rhs) const
{
	return x * rhs.x + y * rhs.y;
}

float Vector2::cross(const Vector2& rhs) const
{
	return x * rhs.y - rhs.x * y;
}

END_OGS_NAMESPACE