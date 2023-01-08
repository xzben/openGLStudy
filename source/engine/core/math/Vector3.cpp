#include "Vector3.h"
#include <cmath>

BEGIN_OGS_NAMESPACE

IMPLEMENT_CLASS_BASE(Vector3)

BEGIN_REFLEX_CLASS_FIELD(Vector3)
REFLEX_FIELD(float, x)
REFLEX_FIELD(float, y)
REFLEX_FIELD(float, z)
END_REFLEX_CLASS_FIELD()

float Vector3::length() const
{
	return std::sqrt(x * x + y * y + z * z);
}

void Vector3::normalize()
{
	float n = x * x + y * y + z * z;
	if (n == 1.f || n == 0.f) return;

	n = std::sqrt(n);

	n = 1.0f/n;
	x *= n;
	y *= n;
	z *= n;
}

float Vector3::dot(const Vector3& rhs) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vector3 Vector3::cross(const Vector3& rhs) const
{
	Vector3 r;

	r.x = y * rhs.z - z * rhs.y;
	r.y = z * rhs.x - x * rhs.z;
	r.z = x * rhs.y - y * rhs.x;

	return r;
}
END_OGS_NAMESPACE